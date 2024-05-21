// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentSlotWidget.generated.h"

class UImage;
class UTexture2D;
class UItemBase;
class UEquipmentTooltip;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECTD_API UEquipmentSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetItem( UItemBase* ItemBase );

	FORCEINLINE UItemBase* GetItem() const { return ItemReference;}

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

protected:
	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UImage* MainIcon;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UImage* ItemIcon;

	UPROPERTY( VisibleAnywhere , Category = "Inventory Slot" , meta = (BindWidget) )
	UButton* HorveredButton;

	UPROPERTY()
	UItemBase* ItemReference;

	UPROPERTY()
	UEquipmentTooltip* Tooltip;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UEquipmentTooltip> TooltipFactory;

private:
	UFUNCTION()
	void VisibleTooltip();

	UFUNCTION()
	void UnVisibleTooltip();
};
