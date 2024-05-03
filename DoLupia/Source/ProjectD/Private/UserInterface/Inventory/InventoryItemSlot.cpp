﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Characters/Components/InventoryComponent.h"
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
		Tooltip = CreateWidget<UInventoryTooltip>(this, ToolTipFactory);
		Tooltip->SetInventoryItemSlotBeingHovered(this);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
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

	if(DragItemVisualFactory && ItemReference)
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
		DragItemOperation->SetInventoryItemSlot(this);

		DragItemOperation->DefaultDragVisual = DragItemVisual;
		DragItemOperation->Pivot = EDragPivot::CenterLeft;

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
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>( InOperation );

	// 플레이어가 아이템을 드래그 앤 드랍 할 수 있도록 설정
	UInventoryItemSlot* InventoryItemSlot = ItemDragDrop->GetInventoryItemSlot();
	UItemBase* ItemBase = ItemDragDrop->GetSourceItem();
	if (ItemBase && !InventoryItemSlot->IsEmpty())
	{
		if(ItemBase == this->ItemReference)
			return false;

		UInventoryComponent* InventoryComponent = ItemBase->GetOwningInventory();
		InventoryComponent->SwapInventory(InventoryItemSlot, this);

		if (this->ItemReference)
		{
			InventoryItemSlot->SetItemReference( this->ItemReference );
			this->ItemReference = ItemBase;

			InventoryItemSlot->GetToolTip()->SetupTooltip();
			InventoryItemSlot->RefreshItemSlot();

			this->Tooltip->SetupTooltip();
			this->RefreshItemSlot();
		}
		else
		{
			InventoryItemSlot->SetItemReference( this->ItemReference );
			this->ItemReference = ItemBase;

			this->Tooltip->SetupTooltip();
			this->RefreshItemSlot();

			InventoryItemSlot->ResetItemSlot();
		}




		return true;

	}

	return false;

	//return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryItemSlot::RefreshItemSlot()
{
	if (ItemReference)
	{
		bIsEmpty = false;

		if(!Tooltip)
		{
			Tooltip = CreateWidget<UInventoryTooltip>( this , ToolTipFactory );
			UE_LOG(LogTemp, Error, TEXT("UInventoryItemSlot::RefreshItemSlot : Tooltip error"));
		}
			
			
		SetToolTip( Tooltip );


		switch (ItemReference->GetItemQuality())
		{
		case EItemQuality::Shoddy:
			ItemBorder->SetBrushColor( FLinearColor::Gray );
			break;
		case EItemQuality::Common:
			ItemBorder->SetBrushColor( FLinearColor::White );
			break;
		case EItemQuality::Quality:
			ItemBorder->SetBrushColor( FLinearColor( 0.0f , 0.51f , 0.169f ) );
			break;
		case EItemQuality::Masterwork:
			ItemBorder->SetBrushColor( FLinearColor( 0.0f , 0.4f , 0.75f ) );
			break;
		case EItemQuality::Grandmaster:
			ItemBorder->SetBrushColor( FLinearColor( 1.0f , 0.45f , 0.0f ) ); // orange
			break;
		default:;
		}

		ItemIcon->SetBrushFromTexture( ItemReference->GetAssetData().Icon );

		if (ItemReference->GetNumericData().bIsStackable)
		{
			ItemQuantity->SetVisibility( ESlateVisibility::Visible );
			ItemQuantity->SetText( FText::AsNumber( ItemReference->GetQuantity() ) );
			UE_LOG(LogTemp, Warning, TEXT( "UInventoryItemSlot::RefreshItemSlot() : %s" ) , *FText::AsNumber( ItemReference->GetQuantity()).ToString());

		}
		else
		{
			ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );
		}
	}
}

void UInventoryItemSlot::ResetItemSlot()
{
	ItemBorder->SetBrushColor( FLinearColor::White );
	ItemIcon->SetBrushFromTexture( nullptr );
	ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );

	bIsEmpty = true;

	SetToolTip( nullptr );
}
