// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentTooltip.generated.h"

class UEquipmentSlotWidget;
class UTextBlock;
class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API UEquipmentTooltip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupTooltip( UItemBase* ItemBase );

protected:
	UPROPERTY( meta = (BindWidget) )
	UTextBlock* ItemName;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* ItemType;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* DamageValue;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* ArmorRating;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* UsageText;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* ItemDescription;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* SellValue;

	UPROPERTY( meta = (BindWidget) )
	UTextBlock* StackWeight;

};
