// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Event/LocationTitleWidget.h"
#include "Components/TextBlock.h"

void ULocationTitleWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (txt_LocationName)
	{
		if (!LocationTitleText.IsEmpty())
		{
			FText OT_Text = FText::FromString( LocationTitleText );
			txt_LocationName->SetText( OT_Text );
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "LocationTitleText is empty in NativePreConstruct" ) );
		}
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "txt_LocationName is null in NativePreConstruct" ) );
	}
}

void ULocationTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

    if (ani_Title)
    {
        PlayAnimation( ani_Title , 0.0f , 1 , EUMGSequencePlayMode::Forward , 1.0f );
    }
    else
    {
        UE_LOG( LogTemp , Warning , TEXT( "ani_Title is null in NativeConstruct" ) );
    }

	UWorld* World = GetWorld();
    if (World)
    {

        FTimerHandle TimerHandle;

        World->GetTimerManager().SetTimer(
            TimerHandle ,
            [this]() {
            	RemoveFromParent();
            } ,
            1.5f ,
            false
        );
    }
    else
    {
        UE_LOG( LogTemp , Warning , TEXT( "World is null in NativeConstruct" ) );
    }
}
