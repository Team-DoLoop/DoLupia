// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/NPC/DialogWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Quest/Dialogsystem/DialogComponent.h"


void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_nxt->OnClicked.AddDynamic( this , &UDialogWidget::OnNxtBtnClicked );
}

void UDialogWidget::UpdateDialogText(FText NewText)
{
	if (txt_dialog)
	{
		txt_dialog->SetText( NewText );
	}
}

void UDialogWidget::UpdateSpeakerText(FText NewSpeaker)
{
	if(txt_speaker)
	{
		txt_speaker->SetText( NewSpeaker );
	}
}

void UDialogWidget::SetCurrentNPC(AActor* InCurrentNPC)
{
    UE_LOG( LogTemp , Warning , TEXT( "UDialogWidget::SetCurrentNPC" ) );
    CurrentNPC = InCurrentNPC;
}

void UDialogWidget::OnNxtBtnClicked()
{
    UE_LOG( LogTemp , Warning , TEXT( "UDialogWidget::OnNxtBtnClicked" ) );
    if (CurrentNPC)
    {
        UE_LOG( LogTemp , Warning , TEXT( "UDialogWidget::OnNxtBtnClicked - CurrentNPC" ) );
        UDialogComponent* DialogueComponent = CurrentNPC->FindComponentByClass<UDialogComponent>();
        if (DialogueComponent)
        {
            UE_LOG( LogTemp , Warning , TEXT( "UDialogWidget::OnNxtBtnClicked - DialogueComponent" ) );
            DialogueComponent->AdvanceDialog();
        }
    }
}
