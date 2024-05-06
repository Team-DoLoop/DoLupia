// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/WidgetQuestGiver.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/ProjectDPlayerController.h"

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
        PlayerControllerD->bShowMouseCursor = true;
    }
    
}

void UWidgetQuestGiver::OnAcceptClicked()
{

}

void UWidgetQuestGiver::OnDeclineClicked()
{
    RemoveFromParent();
}

void UWidgetQuestGiver::OnMouseChange()
{

}
