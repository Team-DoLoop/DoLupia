// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Event/PlayerDieWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPlayerDieWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_ReStart->OnClicked.AddDynamic(this, &UPlayerDieWidget::ReStart);
	Btn_Quit->OnClicked.AddDynamic(this, &UPlayerDieWidget::Quit);
}

void UPlayerDieWidget::ReStart()
{
	FString mapName = UGameplayStatics::GetCurrentLevelName ( GetWorld ( ) );
	UGameplayStatics::OpenLevel ( GetWorld ( ) , FName ( *mapName ) );

	this->RemoveFromParent ( );
	auto controller = GetWorld ( )->GetFirstPlayerController ( );
	controller->SetShowMouseCursor ( false );
	controller->SetInputMode ( FInputModeGameOnly ( ) );
}

void UPlayerDieWidget::Quit()
{
	auto controller = GetWorld ( )->GetFirstPlayerController ( );
	UKismetSystemLibrary::QuitGame ( GetWorld ( ) , controller , EQuitPreference::Quit , false );
}
