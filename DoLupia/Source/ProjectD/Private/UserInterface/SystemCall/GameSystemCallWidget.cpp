// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/SystemCall/GameSystemCallWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"

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
    if (SoundCue)
    {
        //USoundBase* PooledSound = GetPooledSound();
        //if (PooledSound)
        {
            // 사운드 플레이
            //UGameplayStatics::PlaySound( this , SoundCue , Location );
        }
    }

    DisplayMessage( Message );
}

void UGameSystemCallWidget::DisplayMessage( const FText& Message , USoundWave* SoundWave )
{
    //if (SoundWave)
    //{
    //    USoundBase* PooledSound = GetPooledSound();
    //    if (PooledSound)
    //    {
    //        // 사운드 플레이
    //        UGameplayStatics::PlaySoundAtLocation( this , SoundWave , Location );
    //        ReturnSoundToPool( PooledSound );
    //    }
    //}

    DisplayMessage( Message );
}


