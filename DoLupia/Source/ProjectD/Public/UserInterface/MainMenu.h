﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AProjectDCharacter;
class UInventoryPannel;
class UMainQuickSlotWidget;
class UPlayerEquipmentWidget;

/**
 * 
 */
UCLASS()
class PROJECTD_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


public:
	FORCEINLINE UInventoryPannel* GetInventoryPanel() const { return InventoryPanel; };
	FORCEINLINE UPlayerEquipmentWidget* GetPlayerEquipmentWidget() const { return PlayerEquipmentWidget; };

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	UPROPERTY(meta=(BindWidget))
	UInventoryPannel* InventoryPanel;

	UPROPERTY( meta = (BindWidget) )
	UPlayerEquipmentWidget* PlayerEquipmentWidget;

	UPROPERTY()
	AProjectDCharacter* PlayerCharacter;

	
};
