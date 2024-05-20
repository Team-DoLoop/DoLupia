// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDefaultsWidget.generated.h"

class UMainQuickSlotWidget;
class UQuickSlotWidget;
class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerDefaultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UMainQuickSlotWidget* GetMainQuickSlot() const { return QuickSlot; }
	//FORCEINLINE void SetMainQuickSlotWidget( UMainQuickSlotWidget* NewQuickSlot ) { QuickSlot = NewQuickSlot; }

	void UseQuickSlot(int32 SlotNumber );
	void RefreshQuickSlot( const FString& ItemName , int32 NewQuantity) const;

	UQuickSlotWidget* FindQuickSlot(int32 FindIndex);

protected:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMainQuickSlotWidget> QuickSlotFactory;

	UPROPERTY()
	UMainQuickSlotWidget* QuickSlot;
};
