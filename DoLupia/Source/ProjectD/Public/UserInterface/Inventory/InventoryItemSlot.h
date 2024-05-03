// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemSlot.generated.h"

class UItemBase;
class UDragItemVisual;
class UInventoryTooltip;
class UBorder;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTD_API UInventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// setter
	FORCEINLINE void SetItemReference(UItemBase* ItemIn) { ItemReference = ItemIn; }
	FORCEINLINE void SetSlotIndex(int32 NewSlotIndex) { SlotIndex = NewSlotIndex; }

	// getter
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; }
	FORCEINLINE UInventoryTooltip* GetToolTip() const { return Tooltip; }
	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }

	void RefreshItemSlot();
	void ResetItemSlot();

protected:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UDragItemVisual> DragItemVisualFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
	TSubclassOf<UInventoryTooltip> ToolTipFactory;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot")
	UItemBase* ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Inventory Slot", meta = (BindWidget))
	UTextBlock* ItemQuantity;

	int32 SlotIndex;

	TObjectPtr<UInventoryTooltip> Tooltip;

};
