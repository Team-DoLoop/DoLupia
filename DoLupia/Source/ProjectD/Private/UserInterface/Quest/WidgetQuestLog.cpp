#include "UserInterface/Quest/WidgetQuestLog.h" // 클래스에 대한 헤더

#include "Characters/ProjectDCharacter.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Quest/QuestLogComponent.h" // QuestLogComponent에 대한 헤더
#include "UserInterface/Quest/WidgetQuestLog_QuestEntry.h"
#include "UserInterface/Quest/WidgetQuestLog_Objective.h"
#include "UserInterface/Quest/QuestTracker.h"

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

    AProjectDCharacter* PlayerCharacterD = Cast<AProjectDCharacter>(PlayerCharacter);
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
        FInputModeGameAndUI InputMode;
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

    WidgetSwitcher->SetActiveWidgetIndex( 1 );

    box_Objectives->ClearChildren();

    FQuestDetails* QuestDetialsRow = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );

    if(QuestDetialsRow)
    {
	    FText QN_MyText = FText::FromString( QuestDetialsRow->QuestName );
		txt_QuestName->SetText( QN_MyText );
		FText TD_MyText = FText::FromString( QuestDetialsRow->TrackingDescription );
    	txt_QuestDesc->SetText( TD_MyText );
    	FText SD_MyText = FText::FromString( QuestDetialsRow->Stages[0].Description );
    	txt_StageDesc->SetText( SD_MyText );

        for (const auto& Objective : QuestDetialsRow->Stages[0].Objectives) // 범위 기반 for 루프
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
}

void UWidgetQuestLog::OnTracked( AQuest_Base* QuestActor )
{
    if (IsValid( Tracker ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Tracker is valid." ) );

        // Tracker가 이미 존재하면 Update 호출
        Tracker->Remove();
        Tracker = nullptr;
        Tracker = CreateWidget<UQuestTracker>( GetWorld() , QuestTracker_Widget );

        if (IsValid( Tracker ))
        {
            Tracker->QuestActor = QuestActor;
            Tracker->AddToViewport( -1 );

            // 초기화 호출
            Tracker->WidgetUpdate();
        }
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "Tracker is not valid." ) );

        // Tracker가 존재하지 않으면 새로 생성
        Tracker = CreateWidget<UQuestTracker>( GetWorld() , QuestTracker_Widget );

        if (IsValid( Tracker ))
        {
            Tracker->QuestActor = QuestActor;
            Tracker->AddToViewport( -1 );

            // 초기화 호출
            Tracker->WidgetUpdate();
        }
    }
}

void UWidgetQuestLog::AddQuestToScrollBox(UWidgetQuestLog_QuestEntry* QuestWidget, FQuestDetails* QuestDetailsRow, FName QuestID)
{
    if (!IsValid( scroll_MainQuests ))
    {
        UE_LOG( LogTemp , Error , TEXT( "scroll_MainQuests is not valid." ) );
        return;
    }
    if (!IsValid( scroll_SideQuests ))
    {
        UE_LOG( LogTemp , Error , TEXT( "scroll_SideQuests is not valid." ) );
        return;
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
