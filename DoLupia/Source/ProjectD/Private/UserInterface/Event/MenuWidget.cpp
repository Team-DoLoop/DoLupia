// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Event/MenuWidget.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/LevelManager.h"

void UMenuWidget::NativeConstruct()
{
	Btn_Lobby->OnClicked.AddDynamic( this , &UMenuWidget::GotoLobby );
	Btn_Restart->OnClicked.AddDynamic( this , &UMenuWidget::Restart );

}

void UMenuWidget::Restart()
{
	RemoveFromParent();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController( GetWorld() , 0 ))
	{
		PC->SetPause( false );
	}
}

void UMenuWidget::GotoLobby()
{
	UGameplayStatics::OpenLevel( GetWorld() , "Opening" );
}

void UMenuWidget::OpenMenu()
{
    if (IsInViewport())
    {
        RemoveFromParent();

        if (APlayerController* PC = UGameplayStatics::GetPlayerController( GetWorld() , 0 ))
        {
            PC->SetPause( false );
        }
    }
    else
    {
        AddToViewport();

        if (APlayerController* PC = UGameplayStatics::GetPlayerController( GetWorld() , 0 ))
        {
            PC->SetPause( true );
        }
    }
}
