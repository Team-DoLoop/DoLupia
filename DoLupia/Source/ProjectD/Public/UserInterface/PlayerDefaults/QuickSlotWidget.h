// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotWidget.generated.h"

class UImage;
class UTextBlock;
class UQuickSlotDragDropOperation;
class UMainQuickSlotWidget;
class UDragQuickSlotVisual;
class UItemBase;
class UTexture2D;
class UButton;

DECLARE_DELEGATE_TwoParams( FItemDelegateQuantityCalled, FString, int32 );

/**
 * 
 */
UCLASS()
class PROJECTD_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetIndex() const { return Index;}
	FORCEINLINE void InitQuickSlotWidget(int32 NewIndex, UMainQuickSlotWidget* NewMainQuickSlotWidget)
	{
		Index = NewIndex;
		MainQuickSlotWidget = NewMainQuickSlotWidget;
	}

	FORCEINLINE UItemBase* GetItemBase() const { return ItemReference; }

	bool IsHoveredButton() const;

	void UseItem();

	bool HandleQuickSlot( UQuickSlotWidget* OtherQuickSlot );

	void ReleaseQuickSlot( UQuickSlotWidget* ReleasedQuickSlot ) const;

	bool CheckHorveredQuickSlotUI( const FVector2D& MousePosition );

	FItemDelegateQuantityCalled QuantityCalled;

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry , const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:
	void HorveredQuickSlotUI();
	void UnHorveredQuickSlotUI(bool IsInputModeGameOnly );
	void DraggingQuickSlotUI();
	void MouseUpQuickSlotUI();

	UFUNCTION()
	void SetQuantity(FString ItemID , int32 NewQuantity) const;

	bool SwapQuickSlot( UQuickSlotWidget* OtherQuickSlot );

	UFUNCTION()
	void TimerSwapQuickSlot();

private:
	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* MainIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemQuantity;

	UPROPERTY( EditDefaultsOnly , Category = "Quick Slot" )
	TSubclassOf<UDragQuickSlotVisual> DragQuickSlotVisualFactory;

	UPROPERTY( EditDefaultsOnly, Category = "BackBoard Images")
	UTexture2D* BackBoardTexture;

	UPROPERTY()
	UItemBase* ItemReference;

	UPROPERTY()
	UMainQuickSlotWidget* MainQuickSlotWidget;

	UPROPERTY()
	APlayerController* PlayerController;

	int32 Index;

	bool Clicked = false;
	bool Hovered = false;
	bool IsFullScreen = false;
};
