// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/DoLupiaHUD.h"

#include "UserInterface/MainMenu.h"
#include "UserInterface/Interaction/InteractionWidget.h"

ADoLupiaHUD::ADoLupiaHUD()
{
}

void ADoLupiaHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MainMenuFactory)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuFactory);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetFactory)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetFactory);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ADoLupiaHUD::DisPlayMenu()
{
	if(MainMenuWidget)
	{
		bISMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ADoLupiaHUD::HideMenu()
{
	if (MainMenuWidget)
	{
		bISMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ADoLupiaHUD::ToggleMenu()
{
	if(bISMenuVisible)
	{
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisPlayMenu();

		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void ADoLupiaHUD::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ADoLupiaHUD::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ADoLupiaHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) const
{
	if (InteractionWidget)
	{
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractableData);
	}
}

