// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainQuickSlotWidget.generated.h"

class UQuickSlotWidget;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class PROJECTD_API UMainQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget1() const { return QuickSlot1; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget2() const { return QuickSlot2; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget3() const { return QuickSlot3; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget4() const { return QuickSlot4; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget5() const { return QuickSlot5; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget6() const { return QuickSlot6; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget7() const { return QuickSlot7; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget8() const { return QuickSlot8; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget9() const { return QuickSlot9; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget0() const { return QuickSlot0; }

	void SwapQuickSlot(UQuickSlotWidget* OnClickedQuickSlot);
	bool IsDraggingWidget();

protected:
	virtual void NativeConstruct() override;
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

protected:
	UPROPERTY( meta = (BindWidget) )
	UCanvasPanel* DefaultsPanel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot3;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot4;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot5;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot6;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot7;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot8;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot9;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UQuickSlotWidget> QuickSlot0;

private:
	TArray<TObjectPtr<UQuickSlotWidget>> QuickSlotArray;

};
