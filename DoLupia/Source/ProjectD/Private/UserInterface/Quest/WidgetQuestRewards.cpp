// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/WidgetQuestRewards.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/ProjectDPlayerController.h"
#include "Quest/QuestLogComponent.h"
#include "Characters/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/Quest/WidgetQuestLog_Objective.h"

void UWidgetQuestRewards::NativePreConstruct()
{

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

}

void UWidgetQuestRewards::NativeConstruct()
{
    if (btn_Accept)
    {
        btn_Accept->OnClicked.AddDynamic( this , &UWidgetQuestRewards::OnAcceptClicked );
    }

    if (btn_Decline)
    {
        btn_Decline->OnClicked.AddDynamic( this , &UWidgetQuestRewards::OnDeclineClicked );
    }

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

    if (PlayerControllerD) {
        FInputModeUIOnly InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
}

void UWidgetQuestRewards::NativeDestruct()
{
    Super::NativeDestruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );
        FInputModeGameAndUI InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
}

void UWidgetQuestRewards::OnAcceptClicked()
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
    //아이템 삭제, 제공

    // UInventoryComponent 찾기
    UInventoryComponent* InvetoryComp = Cast<UInventoryComponent>( PlayerCharacterD->GetComponentByClass( UInventoryComponent::StaticClass() ) );

    //Delete(ObjectiveItems)
    auto RemoveItem = QuestDetails.Stages.GetData()->Objectives;
    for (const auto& removeItem : RemoveItem)
    {
        FString ItemLog;
        for (const auto& Pair : removeItem.ItemObjectives)
        {
            ItemLog += FString::Printf( TEXT( "(%s, %d) " ) , *Pair.Key , Pair.Value );
        }
        UE_LOG( LogTemp , Warning , TEXT( "Removing item: %s" ) , *ItemLog );

        InvetoryComp->HandelRemoveItem( removeItem.ItemObjectives );
    }
    
    InvetoryComp->HandelAddItem( ItemRewards );

    // 위젯을 화면에서 제거합니다.
    RemoveFromParent();
}

void UWidgetQuestRewards::OnDeclineClicked()
{
    RemoveFromParent();
}
