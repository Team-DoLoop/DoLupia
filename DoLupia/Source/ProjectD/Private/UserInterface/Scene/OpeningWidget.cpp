﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Scene/OpeningWidget.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/LevelManager.h"

void UOpeningWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Start->OnClicked.AddDynamic( this , &UOpeningWidget::MoveTutorialMap );
	ReStart->OnClicked.AddDynamic( this , &UOpeningWidget::MoveSaveMap );
	End->OnClicked.AddDynamic(this, &UOpeningWidget::GameEnd );
}

void UOpeningWidget::MoveTutorialMap()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Tutorial"));
}

void UOpeningWidget::GameEnd()
{
	UKismetSystemLibrary::QuitGame( GetWorld() , GetWorld()->GetFirstPlayerController() , EQuitPreference::Quit , false );
}

void UOpeningWidget::MoveSaveMap()
{
	LOAD(ESaveType::SAVE_MAIN, "PlayerMainSave", true, false, true);
}
