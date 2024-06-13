﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryTooltip.generated.h"

class UInventoryItemSlot;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTD_API UInventoryTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	const UInventoryItemSlot* GetInventoryItemSlotBeingHovered() const { return InventoryItemSlotBeingHovered; };
	void SetInventoryItemSlotBeingHovered(UInventoryItemSlot* NewInventoryItemSlotBeingHovered)  { InventoryItemSlotBeingHovered = NewInventoryItemSlotBeingHovered; };

	void SetupTooltip();

protected:
	UPROPERTY(VisibleAnywhere)
	UInventoryItemSlot* InventoryItemSlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* ItemQuality;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorRating;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSize;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeight;

	
};
