// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "Data/WidgetData.h"
#include "UserInterface/Equipment/PlayerEquipmentWidget.h"

ADoLupiaHUD::ADoLupiaHUD()
{
}

void ADoLupiaHUD::BeginPlay()
{
	Super::BeginPlay();

	if(MainMenuFactory)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuFactory);
		MainMenuWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Inventory));
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (InteractionWidgetFactory)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetFactory);
		InteractionWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Interaction));
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

bool ADoLupiaHUD::ToggleMenu()
{
	if(MainMenuWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		DisPlayMenu();
		return true;
	}

	HideMenu();
	return false;
}

void ADoLupiaHUD::UpdateEquipmentWidget(UItemBase* ItemBase ) const
{
	MainMenuWidget->GetPlayerEquipmentWidget()->UpdateWidget( ItemBase );
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

