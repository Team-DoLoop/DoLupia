// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootingItemWidget.generated.h"

class UTextBlock;
class UImage;
class UBorder;

/**
 * 
 */
UCLASS()
class PROJECTD_API ULootingItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMyWidget( const FText& ItemName, int32 ItemQuantity, class UTexture2D* ItemImage );

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Quantity;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UImage* Image;

	UPROPERTY(meta = (BindWidget))
	UBorder* Border;

};
