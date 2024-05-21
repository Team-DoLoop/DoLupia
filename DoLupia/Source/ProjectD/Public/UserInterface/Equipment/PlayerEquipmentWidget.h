// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEquipmentWidget.generated.h"

class UEquipmentSlotWidget;
class UItemBase;

UCLASS()
class PROJECTD_API UPlayerEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(UItemBase* ItemBase ) const;

protected:
	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Head;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Top;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Pants;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Weapon;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Gloves;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UEquipmentSlotWidget* Shoes;


};
