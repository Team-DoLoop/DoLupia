// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/WidgetQuestGiver.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Common/UseColor.h"
#include "Components/VerticalBox.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/AIConnectionLibrary.h"
#include "Quest/QuestLogComponent.h"
#include "UserInterface/Quest/WidgetQuestLog_Objective.h"

void UWidgetQuestGiver::NativePreConstruct()
{
    box_Objectives->ClearChildren();

    if (!QuestDetails.QuestName.IsEmpty())
    {
        FText QN_MyText = FText::FromString( QuestDetails.QuestName );
		txt_QuestName->SetText( QN_MyText );
    }

    if (!QuestDetails.LogDescription.IsEmpty())
    {
		FText QD_MyText = FText::FromString( QuestDetails.LogDescription );
		txt_QuestDesc->SetText( QD_MyText );
    }

    if (QuestDetails.Stages.Num() > 0 && !QuestDetails.Stages[0].Description.IsEmpty())
    {
		FText SD_MyText = FText::FromString( QuestDetails.Stages[CurrentStage].Description );
		txt_StageDesc->SetText( SD_MyText );
    }

    if (QuestDetails.Stages.Num() > 0) // 배열이 비어 있지 않은지 확인
    {
        const auto& FirstStage = QuestDetails.Stages[CurrentStage]; // 첫 번째 요소에 접근
        for (const auto& Objective : FirstStage.Objectives) // 범위 기반 for 루프
        {
            UWidgetQuestLog_Objective* ObjectiveWidget = CreateWidget<UWidgetQuestLog_Objective>( GetWorld() , Objective_Widget );
            if (IsValid( ObjectiveWidget ))
            {
                ObjectiveWidget->ObjectiveData = Objective;
                box_Objectives->AddChildToVerticalBox( ObjectiveWidget );
            }
        }
    }
}

void UWidgetQuestGiver::NativeConstruct()
{

    if (btn_Accept)
    {
        btn_Accept->OnClicked.AddDynamic( this , &UWidgetQuestGiver::OnAcceptClicked );
    }

    if (btn_Decline)
    {
        btn_Decline->OnClicked.AddDynamic( this , &UWidgetQuestGiver::OnDeclineClicked );
    }

    SetIsFocusable( true );

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

    if (PlayerControllerD) {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(TakeWidget());
        PlayerControllerD->SetInputMode( InputMode );
    }


}

void UWidgetQuestGiver::NativeDestruct()
{
	Super::NativeDestruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController)
    {
	    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );
        FInputModeGameAndUI InputMode;
        //InputMode.SetConsumeCaptureMouseDown(true);
        PlayerControllerD->SetInputMode( InputMode );
    }
        
}

void UWidgetQuestGiver::OnAcceptClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!IsValid( PlayerController ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerController is not valid." ) );
        return;
    }

    ACharacter* PlayerCharacter = Cast<ACharacter>( PlayerController->GetPawn() );
    if (!IsValid( PlayerCharacter ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerCharacter is not valid." ) );
        return;
    }

	AProjectDCharacter* PlayerCharacterD = Cast<AProjectDCharacter>( PlayerCharacter );

    // 특정 Quest 완료 시, Player 스킬 Unlock
    if( QuestID == "1002" )
    {
        PlayerCharacterD->GetAttackComp()->SetSkillUseState( true , ESkillOpenType::QUEST );
        PlayerCharacterD->GetAttackComp()->SetColorUseState( EUseColor::RED , true );
    }
    // 첫 퀘스트(아무색 없다가 Red라도 생기는 경우) or 무기 장착한 경우
    

    // 캐릭터에서 QuestLogComponent를 찾습니다.
    UQuestLogComponent* QuestLogComp = Cast<UQuestLogComponent>( PlayerCharacterD->GetComponentByClass( UQuestLogComponent::StaticClass() ) );
    if (!IsValid( QuestLogComp ))
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestLogComponent is invalid or not found on PlayerCharacter." ) );
        return;
    }

    if (QuestID.IsNone())
    {
        UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ WidgetQuestGiver" ) );
    }

    // 컴포넌트가 유효할 경우, 퀘스트를 추가합니다.
    // 수락을 하면!!!!!
    QuestLogComp->AddNewQuest( QuestID );

    //AI 서버에 보내기(망토 색깔)
   auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
   auto AIlib = gm->GetAIConnectionLibrary();
   FString tmpString = QuestID.ToString();
   int32 tmpNum = FCString::Atoi( *tmpString );
   UE_LOG( LogTemp , Error , TEXT( "tmpNum : %d" ) , tmpNum );
   AIlib->SendPImgToSrv( tmpNum );

   //AI*/

    // 위젯을 화면에서 제거합니다.
    RemoveFromParent();
}

void UWidgetQuestGiver::OnDeclineClicked()
{
    RemoveFromParent();
}
