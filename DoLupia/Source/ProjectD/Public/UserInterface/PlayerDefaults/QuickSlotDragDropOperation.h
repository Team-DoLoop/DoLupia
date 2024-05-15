// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "QuickSlotDragDropOperation.generated.h"

class UQuickSlotWidget;
class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API UQuickSlotDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	// getter
	FORCEINLINE UItemBase* GetSourceItem() const { return SourceItem; };
	FORCEINLINE UQuickSlotWidget* GetQuickSlotItem() const { return SourceQuickSlotWidget; };

	// setter
	FORCEINLINE void SetSourceItem( UItemBase* NewSourceItem ) { SourceItem = NewSourceItem; };
	FORCEINLINE void SetQuickSlotItem( UQuickSlotWidget* NewSourceQuickSlotWidget ) { SourceQuickSlotWidget = NewSourceQuickSlotWidget; };

private:
	UPROPERTY()
	UItemBase* SourceItem;

	UPROPERTY()
	UQuickSlotWidget* SourceQuickSlotWidget;
};
