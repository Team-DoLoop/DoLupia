﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/WidgetQuestGiver.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/ProjectDPlayerController.h"
#include "Components/VerticalBox.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/WidgetQuestLog_Objective.h"

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
		FText SD_MyText = FText::FromString( QuestDetails.Stages[0].Description );
		txt_StageDesc->SetText( SD_MyText );
    }

    if (QuestDetails.Stages.Num() > 0) // 배열이 비어 있지 않은지 확인
    {
        const auto& FirstStage = QuestDetails.Stages[0]; // 첫 번째 요소에 접근
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

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

    if (PlayerControllerD) {
        FInputModeUIOnly InputMode;
        //if(btn_Accept)
            //InputMode.SetWidgetToFocus(btn_Accept);
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
        FInputModeGameOnly InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
        
}

void UWidgetQuestGiver::OnAcceptClicked()
{
    APlayerController* OwningPlayer = GetOwningPlayer();

    if (OwningPlayer == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "OwningPlayer is null." ) );
        return;
    }

    // 플레이어 캐릭터를 찾습니다.
    ACharacter* PlayerCharacter = OwningPlayer->GetCharacter(); // 플레이어 컨트롤러가 소유한 캐릭터
    if (PlayerCharacter == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "PlayerCharacter is null." ) );
        return;
    }
	AProjectDCharacter* PlayerCharacterD = Cast<AProjectDCharacter>( PlayerCharacter );

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
    UE_LOG( LogTemp , Error , TEXT( "QuestID: %s" ) , *QuestID.ToString() );

    // 컴포넌트가 유효할 경우, 퀘스트를 추가합니다.
    QuestLogComp->AddNewQuest( QuestID );

    // 위젯을 화면에서 제거합니다.
    RemoveFromParent();
}

void UWidgetQuestGiver::OnDeclineClicked()
{
    RemoveFromParent();
}
