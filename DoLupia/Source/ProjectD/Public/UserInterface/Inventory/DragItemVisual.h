// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragItemVisual.generated.h"

class UBorder;
class UImage;
class UTextBlock;

UCLASS()
class PROJECTD_API UDragItemVisual : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UBorder* GetItemBorder() const { return ItemBorder; };
	FORCEINLINE UImage* GetItemIcon() const { return ItemIcon; };
	FORCEINLINE UTextBlock* GetItemQuantity() const { return ItemQuantity; };

protected:
	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UBorder* ItemBorder;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UImage* ItemIcon;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item Visual", meta = (BindWidget))
	UTextBlock* ItemQuantity;
	
};
