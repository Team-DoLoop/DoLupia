// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragQuickSlotVisual.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class PROJECTD_API UDragQuickSlotVisual : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UImage* GetMainIcon() const { return MainIcon; };
	FORCEINLINE UImage* GetItemIcon() const { return ItemIcon; };

protected:
	UPROPERTY( VisibleAnywhere , Category = "Drag Item Visual" , meta = (BindWidget) )
	UImage* MainIcon;

	UPROPERTY( VisibleAnywhere , Category = "Drag Item Visual" , meta = (BindWidget) )
	UImage* ItemIcon;

};
