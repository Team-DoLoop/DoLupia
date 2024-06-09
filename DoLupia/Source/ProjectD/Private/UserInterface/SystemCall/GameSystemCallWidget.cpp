// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/SystemCall/GameSystemCallWidget.h"
#include "Components/TextBlock.h"
#include "Pooling/SoundManager.h"

void UGameSystemCallWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SystemText->SetRenderOpacity(0.0f);
}

void UGameSystemCallWidget::DisplayMessage( const FText& Message )
{
    SystemText->SetText( Message );
    PlayAnimation( FadeAnimation );
}

void UGameSystemCallWidget::DisplayMessage( const FText& Message , USoundCue* SoundCue )
{
    ASoundManager::GetInstance( GetWorld() )->PlaySoundCue2D( SoundCue, EPlayerSound::PlayerSound9 );
    DisplayMessage( Message );
}

void UGameSystemCallWidget::DisplayMessage( const FText& Message , USoundWave* SoundWave )
{
    ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( SoundWave, EPlayerSound::PlayerSound9);
    DisplayMessage( Message );
}


