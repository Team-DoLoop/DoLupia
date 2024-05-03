// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UItemBase;
class UInventoryComponent;
class UInventoryItemSlot;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	// getter
	FORCEINLINE UItemBase* GetSourceItem() const { return SourceItem; };
	FORCEINLINE UInventoryComponent* GetSourceInventory() const { return SourceInventory; };
	FORCEINLINE UInventoryItemSlot* GetInventoryItemSlot() const { return InventoryItemSlot; };

	// setter
	FORCEINLINE void SetSourceItem(UItemBase* NewSourceItem) { SourceItem = NewSourceItem; };
	FORCEINLINE void SetSourceInventory(UInventoryComponent* NewSourceInventory) { SourceInventory = NewSourceInventory; };
	FORCEINLINE void SetInventoryItemSlot( UInventoryItemSlot* NewUInventoryItemSlot ) { InventoryItemSlot = NewUInventoryItemSlot; };

private:
	UPROPERTY()
	UItemBase* SourceItem;

	UPROPERTY()
	UInventoryComponent* SourceInventory;

	UPROPERTY()
	UInventoryItemSlot* InventoryItemSlot;
};
