// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/DragItemVisual.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

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
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.51f, 0.169f));
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor(FLinearColor(0.0f, 0.4f, 0.75f));
			break;
		case EItemQuality::Grandmaster:
			ItemBorder->SetBrushColor(FLinearColor(1.0f, 0.45f, 0.0f)); // orange
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
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	// 우클릭 예정
	
	return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(DragItemVisualFactory)
	{
		const TObjectPtr<UDragItemVisual> DragItemVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualFactory);
		DragItemVisual->GetItemIcon()->SetBrushFromTexture(ItemReference->GetAssetData().Icon);
		DragItemVisual->GetItemBorder()->SetBrushColor(ItemBorder->GetBrushColor());

		ItemReference->GetNumericData().bIsStackable 
			? DragItemVisual->GetItemQuantity()->SetText(FText::AsNumber(ItemReference->GetQuantity()))
			: DragItemVisual->GetItemQuantity()->SetVisibility(ESlateVisibility::Collapsed);

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SetSourceItem(ItemReference);
		DragItemOperation->SetSourceInventory(ItemReference->GetOwningInventory());

		DragItemOperation->DefaultDragVisual = DragItemVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft;

		OutOperation = DragItemOperation;
	}
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
