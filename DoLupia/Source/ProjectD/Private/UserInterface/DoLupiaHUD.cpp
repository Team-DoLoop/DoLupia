﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/Interaction/InteractionWidget.h"
#include "Data/WidgetData.h"
#include "Pooling/SoundManager.h"
#include "UserInterface/Equipment/PlayerEquipmentWidget.h"
#include "UserInterface/SystemCall/GameSystemCallWidget.h"

ADoLupiaHUD::ADoLupiaHUD()
{
}

void ADoLupiaHUD::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ADoLupiaHUD::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	if(MainMenuFactory && !MainMenuWidget)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuFactory);
		MainMenuWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Inventory));
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		FFileHelper::SaveStringToFile( L"ADoLupiaHUD::BeginPlay -> MainMenuFactory && !MainMenuWidget" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
			&IFileManager::Get() , ELogVerbosity::Log );
	}

	if (InteractionWidgetFactory && !InteractionWidget)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetFactory);
		InteractionWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Interaction));
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		FFileHelper::SaveStringToFile( L"ADoLupiaHUD::BeginPlay -> InteractionWidgetFactory && !InteractionWidget" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
			&IFileManager::Get() , ELogVerbosity::Log );
	}

	if(GameSystemCallFactory && !GameSystemCall)
	{
		GameSystemCall = CreateWidget<UGameSystemCallWidget>(GetWorld(), GameSystemCallFactory );
		GameSystemCall->AddToViewport(static_cast<uint32>(ViewPortPriority::Behind));
		GameSystemCall->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		FFileHelper::SaveStringToFile( L"ADoLupiaHUD::BeginPlay -> GameSystemCallFactory && !GameSystemCall" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
			&IFileManager::Get() , ELogVerbosity::Log );
	}


	FFileHelper::SaveStringToFile( L"ADoLupiaHUD::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

void ADoLupiaHUD::OnSystemCall(const FText& Message) const
{
	GameSystemCall->DisplayMessage(Message);
}

void ADoLupiaHUD::OnSystemCallSoundCue(const FText& Message, USoundCue* SoundCue) const
{
	GameSystemCall->DisplayMessage( Message, SoundCue );
}

void ADoLupiaHUD::OnSystemCallSoundWave(const FText& Message, USoundWave* SoundWave) const
{
	GameSystemCall->DisplayMessage( Message , SoundWave );
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

