// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/InventoryTooltip.h"

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(ToolTipFactory)
	{
		UInventoryTooltip* Tooltip = CreateWidget<UInventoryTooltip>(this, ToolTipFactory);
		Tooltip->SetInventoryItemSlotBeingHovered(this);
		SetToolTip(Tooltip);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemReference)
	{
		switch (ItemReference->GetItemQuality())
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor(FLinearColor::Gray);
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor(FLinearColor::White);
			break;
		case EItemQuality::Quality:
			ItemBorder->SetBrushColor(FLinearColor::Green);
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor::Blue);
			break;
		case EItemQuality::Grandmaster:
			ItemBorder->SetBrushColor(FLinearColor(100.0f, 65.0f, 0.0f, 1.0f)); // orange
			break;
		default: ;
		}

		ItemIcon->SetBrushFromTexture(ItemReference->GetAssetData().Icon);

		if(ItemReference->GetNumericData().bIsStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->GetQuantity()));
		}
		else
		{
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
