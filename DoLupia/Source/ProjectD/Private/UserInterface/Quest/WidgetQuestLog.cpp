#include "UserInterface/Quest/WidgetQuestLog.h" // 클래스에 대한 헤더

#include "Characters/ProjectDCharacter.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Quest/QuestLogComponent.h" // QuestLogComponent에 대한 헤더
#include "UserInterface/Quest/WidgetQuestLog_QuestEntry.h"
#include "UserInterface/Quest/WidgetQuestLog_Objective.h"

// 필요하다면 다른 인클루드 추가
#include "Components/Button.h" // 버튼 사용
#include "Characters/ProjectDPlayerController.h" // PlayerController 사용

void UWidgetQuestLog::NativePreConstruct()
{
    Super::NativePreConstruct();

    // 데이터 테이블 가져오기
    UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/QuestSystem/QuestDataTable.QuestDataTable"));
    if (!IsObjectValid( DataTable , "DataTable" ))
    {
        return;
    }

    QuestData.DataTable = DataTable;

    // 플레이어 컨트롤러 및 캐릭터 획득
    APlayerController* OwningPlayer = GetOwningPlayer();
    if (!IsObjectValid( OwningPlayer , "OwningPlayer" ))
    {
        return;
    }

    ACharacter* PlayerCharacter = OwningPlayer->GetCharacter();
    if (!IsObjectValid( PlayerCharacter , "PlayerCharacter" ))
    {
        return;
    }

    PlayerCharacterD = Cast<AProjectDCharacter>(PlayerCharacter);
    if (!IsObjectValid( PlayerCharacterD , "PlayerCharacterD" ))
    {
        return;
    }

    // QuestLogComponent 찾기
    UQuestLogComponent* QuestLogComp = Cast<UQuestLogComponent>(PlayerCharacterD->GetComponentByClass(UQuestLogComponent::StaticClass()));
    if (!IsObjectValid( QuestLogComp , "QuestLogComp" ))
    {
        return;
    }

    // 배열을 순회하여 각 퀘스트를 처리
    for (const auto& Quest : QuestLogComp->CurrentQuest)
    {
        UWidgetQuestLog_QuestEntry* QuestWidget = CreateWidget<UWidgetQuestLog_QuestEntry>( GetWorld() , QuestLog_Widget );
        if (!IsValid( QuestWidget ))
        {
            continue;
        }

        QuestWidget->QuestID = Quest->QuestID;
        QuestWidget->QuestActor = Quest;

        FQuestDetails* QuestDetailsRow = QuestData.DataTable->FindRow<FQuestDetails>( Quest->QuestID , TEXT( "Searching for row" ) , true );
        if (!QuestDetailsRow)
        {
            continue;
        }
        AddQuestToScrollBox( QuestWidget , QuestDetailsRow, Quest->QuestID );
    }
}

void UWidgetQuestLog::NativeConstruct()
{
	Super::NativeConstruct();

    if (btn_Close)
    {
        btn_Close->OnClicked.AddDynamic( this , &UWidgetQuestLog::OnButtonClicked );
    }

    SetupPlayerController();
}

void UWidgetQuestLog::NativeDestruct()
{
	Super::NativeDestruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

    if (PlayerControllerD) {
        FInputModeGameOnly InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
}

void UWidgetQuestLog::OnButtonClicked()
{
    RemoveFromParent();
}

void UWidgetQuestLog::OnQuestSelected( FName QuestID, AQuest_Base* QuestActor )
{
    DisplayQuest( QuestID, QuestActor );
}

void UWidgetQuestLog::DisplayQuest( FName QuestID , AQuest_Base* QuestActor )
{
    CurrentQuestActor = QuestActor;

    // 위젯 스위처의 활성화된 위젯 인덱스를 1로 설정
    WidgetSwitcher->SetActiveWidgetIndex( 1 );

    // 기존의 모든 자식 위젯 제거
    box_Objectives->ClearChildren();

    // QuestData.DataTable에서 QuestID에 해당하는 행을 찾음
    FQuestDetails* QuestDetailsRow = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );

    // 행이 유효한지 확인
    if (QuestDetailsRow)
    {
        // QuestName 설정
        FText QN_MyText = FText::FromString( QuestDetailsRow->QuestName );
        txt_QuestName->SetText( QN_MyText );

        // TrackingDescription 설정
        FText TD_MyText = FText::FromString( QuestDetailsRow->TrackingDescription );
        txt_QuestDesc->SetText( TD_MyText );

        // CurrentStage가 Stages 배열의 유효한 인덱스인지 확인
        if (QuestDetailsRow->Stages.IsValidIndex( CurrentQuestActor->CurrentStage ))
        {
            FText SD_MyText = FText::FromString( QuestDetailsRow->Stages[CurrentQuestActor->CurrentStage].Description );
            txt_StageDesc->SetText( SD_MyText );

            // Objectives를 순회하면서 위젯 생성 및 추가
            for (const auto& Objective : QuestDetailsRow->Stages[CurrentQuestActor->CurrentStage].Objectives)
            {
                UWidgetQuestLog_Objective* ObjectiveWidget = CreateWidget<UWidgetQuestLog_Objective>( GetWorld() , Objective_Widget );
                if (IsValid( ObjectiveWidget ))
                {
                    ObjectiveWidget->ObjectiveData = Objective;
                    ObjectiveWidget->QuestActor = CurrentQuestActor;
                    box_Objectives->AddChildToVerticalBox( ObjectiveWidget );
                }
            }
        }
        else
        {
            UE_LOG( LogTemp , Error , TEXT( "CurrentStage %d is out of bounds for Stages array of size %d" ) , CurrentQuestActor->CurrentStage , QuestDetailsRow->Stages.Num() );
        }
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestDetailsRow is null for QuestID %s" ) , *QuestID.ToString() );
    }
}

void UWidgetQuestLog::OnTracked( AQuest_Base* QuestActor )
{
    UQuestLogComponent* QuestLogComp = Cast<UQuestLogComponent>( PlayerCharacterD->GetComponentByClass( UQuestLogComponent::StaticClass() ) );
    QuestLogComp->TrackQuest( QuestActor );
}

void UWidgetQuestLog::AddQuestToScrollBox(UWidgetQuestLog_QuestEntry* QuestWidget, FQuestDetails* QuestDetailsRow, FName QuestID)
{
    if (IsValid( scroll_MainQuests ))
    {
        scroll_MainQuests->ClearChildren();
    }
    if (IsValid( scroll_SideQuests ))
    {
        scroll_SideQuests->ClearChildren();
    }

    UScrollBox* SelectedScrollBox = nullptr;
	SelectedScrollBox = QuestDetailsRow->IsMainQuest ? scroll_MainQuests : scroll_SideQuests;

    if (IsValid( SelectedScrollBox ))
    {
        SelectedScrollBox->AddChild( QuestWidget ); // 선택된 스크롤 박스에 위젯 추가
        //여기서 questEntry의 방송을 구독하는 것!! QuestID, QuestActor받을 수 있음
        QuestWidget->OnQuestSelected.AddDynamic( this , &UWidgetQuestLog::OnQuestSelected );

        //tracked 관련 구독 QuestActor 받음
        QuestWidget->OnTracked.AddDynamic( this , &UWidgetQuestLog::OnTracked );
    }
    else
    {
        UE_LOG( LogTemp , Warning , TEXT( "SelectedScrollBox is not valid." ) );
    }
}

void UWidgetQuestLog::SetupPlayerController()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!IsObjectValid( PlayerController , "PlayerController" ))
    {
        return;
    }

    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );
    if (IsValid( PlayerControllerD ))
    {
        FInputModeUIOnly InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
}
