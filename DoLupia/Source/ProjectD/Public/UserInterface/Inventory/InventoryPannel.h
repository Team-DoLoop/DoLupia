// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPannel.generated.h"

class AProjectDCharacter;
class UInventoryComponent;
class UInventoryItemSlot;
class UWrapBox;
class UTextBlock;
class UItemBase;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECTD_API UInventoryPannel : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshInventory();
	void RefreshInventoryPannel(const int32 Index , UItemBase* ItemIn);

protected:
	//void SetInfoText() const;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UWrapBox* InventoryPanel;

	/*UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* WeightInfo;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* CapacityInfo;*/
	

	UPROPERTY( VisibleAnywhere, meta = (BindWidget))
	UButton* SortButton;

	/*	UPROPERTY( VisibleAnywhere , meta = (BindWidget) )
	class UEditableText* MyTest;

	UPROPERTY( VisibleAnywhere , meta = (BindWidget) )
	UButton* TestButton;*/


	UPROPERTY()
	AProjectDCharacter* PlayerCharacter;

	UPROPERTY()
	UInventoryComponent* InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryItemSlot> InventorySlotFactory;

private:
	UFUNCTION()
	void SortItem();

	/*	UFUNCTION()
	void FindItem();*/
	
};
