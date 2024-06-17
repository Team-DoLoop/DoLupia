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
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget1() { return QuickSlot1; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget2() { return QuickSlot2; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget3() { return QuickSlot3; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget4() { return QuickSlot4; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget5() { return QuickSlot5; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget6() { return QuickSlot6; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget7() { return QuickSlot7; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget8() { return QuickSlot8; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget9() { return QuickSlot9; }
	FORCEINLINE UQuickSlotWidget* GetQuickSlotWidget0() { return QuickSlot0; }

	void SwapQuickSlot(UQuickSlotWidget* OnClickedQuickSlot);
	bool IsDraggingWidget();

	bool QuickSlotMouseHoveredWidget( const FVector2D& MousePosition );

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
	UPROPERTY()
	TArray<TObjectPtr<UQuickSlotWidget>> QuickSlotArray;

	UPROPERTY()
	class APlayerController* PlayerController;

};
