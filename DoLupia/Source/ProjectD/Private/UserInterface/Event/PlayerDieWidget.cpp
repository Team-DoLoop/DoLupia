// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Event/PlayerDieWidget.h"

#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/LevelManager.h"

void UPlayerDieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_ReStart->OnClicked.AddDynamic(this, &UPlayerDieWidget::ReStart);
	Btn_Quit->OnClicked.AddDynamic(this, &UPlayerDieWidget::Quit);
}

void UPlayerDieWidget::ReStart()
{

	FString mapName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
	UGameplayStatics::OpenLevel( GetWorld() , FName( *mapName ) );

	//FTimerHandle TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer( TimerHandle, FTimerDelegate::CreateLambda([this]()
	//{
	//	LOAD( ESaveType::SAVE_MAIN , "PlayerMainSave" , true , false , false );
	//}), 0.05f, false);

	//
}

void UPlayerDieWidget::Quit()
{
	auto controller = GetWorld ( )->GetFirstPlayerController ( );
	UKismetSystemLibrary::QuitGame ( GetWorld ( ) , controller , EQuitPreference::Quit , false );
}
