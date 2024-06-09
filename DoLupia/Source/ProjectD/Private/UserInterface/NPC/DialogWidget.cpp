// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/NPC/DialogWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Pooling/SoundManager.h"
#include "Quest/Dialogsystem/DialogComponent.h"


void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_nxt->OnClicked.AddDynamic( this , &UDialogWidget::OnNxtBtnClicked );

    TypingSpeed = 0.05f; 
    CurrentIndex = 0;
}

void UDialogWidget::UpdateDialogText(FText NewText)
{
	if (txt_dialog)
	{
        FullText = NewText;
        CurrentText = "";
        CurrentIndex = 0;

		txt_dialog->SetText( FText::FromString( CurrentText ) );

        // 타이핑 시작
        ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( npcSFX , ENPCSound::NPCSound2 );
        GetWorld()->GetTimerManager().SetTimer( TypingTimerHandle , this , &UDialogWidget::TypeNextCharacter , TypingSpeed , true );
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
    CurrentNPC = InCurrentNPC;
}

void UDialogWidget::OnNxtBtnClicked()
{
    if (CurrentNPC)
    {
        UDialogComponent* DialogueComponent = CurrentNPC->FindComponentByClass<UDialogComponent>();
        if (DialogueComponent)
        {
            DialogueComponent->AdvanceDialog();
            ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D(clickSFX, ENPCSound::NPCSound1, 0.25f);
        }
    }
}

void UDialogWidget::TypeNextCharacter()
{
    if (CurrentIndex < FullText.ToString().Len())
    {
        CurrentText += FullText.ToString()[CurrentIndex];
        txt_dialog->SetText( FText::FromString( CurrentText ) );
        CurrentIndex++;
    }
    else
    {
        // Stop the timer once the full text is displayed
        GetWorld()->GetTimerManager().ClearTimer( TypingTimerHandle );
    }
}
