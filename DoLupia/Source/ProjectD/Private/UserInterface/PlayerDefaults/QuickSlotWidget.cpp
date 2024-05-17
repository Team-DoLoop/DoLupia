﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"
#include "UserInterface/PlayerDefaults/QuickSlotDragDropOperation.h"
#include "UserInterface/PlayerDefaults/DragQuickSlotVisual.h"


void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HoveredButton->OnHovered.AddDynamic( this , &UQuickSlotWidget::HorveredQuickSlotUI );
	HoveredButton->OnUnhovered.AddDynamic(this, &UQuickSlotWidget::UnHorveredQuickSlotUI);

	QuantityCalled.BindUObject(this, &UQuickSlotWidget::SetQuantity);
}

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown( InGeometry , InMouseEvent );

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Test QucikSlot"));
		return Reply.Handled().DetectDrag( TakeWidget() , EKeys::LeftMouseButton );
	}

	return Reply;
}

void UQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                            UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry , InMouseEvent , OutOperation);

	if (DragQuickSlotVisualFactory && ItemReference)
	{
		const TObjectPtr<UDragQuickSlotVisual> DragItemVisual = CreateWidget<UDragQuickSlotVisual>( this , DragQuickSlotVisualFactory );
		DragItemVisual->GetItemIcon()->SetBrushFromTexture( ItemReference->GetAssetData().Icon );
		DragItemVisual->GetMainIcon()->SetBrushFromTexture( BackBoardTexture );

		UQuickSlotDragDropOperation* DragItemOperation = NewObject<UQuickSlotDragDropOperation>();
		DragItemOperation->SetSourceItem( ItemReference );
		DragItemOperation->SetQuickSlotItem( this );

		DragItemOperation->DefaultDragVisual = DragItemVisual;
		DragItemOperation->Pivot = EDragPivot::CenterLeft;

		OutOperation = DragItemOperation;
	}
}

bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                    UDragDropOperation* InOperation)
{
	if(const UQuickSlotDragDropOperation* QuickSlotDragDrop = Cast<UQuickSlotDragDropOperation>( InOperation ))
	{
		if (UItemBase* ItemBase = QuickSlotDragDrop->GetSourceItem())
		{
			if (ItemBase == this->ItemReference)
				return false;

			UQuickSlotWidget* Dest = QuickSlotDragDrop->GetQuickSlotItem();

			const FText& QuantityText = FText::FromString( FString::FromInt(
				ItemBase->GetOwningInventory()->FindItemQuantity( ItemBase->GetTextData().Name.ToString() ) ) );

			ItemIcon->SetBrushFromTexture( ItemBase->GetAssetData().Icon );
			ItemQuantity->SetVisibility(ESlateVisibility::Visible);
			ItemQuantity->SetText( QuantityText );
			ItemReference = Dest->ItemReference;

			Dest->ItemIcon->SetBrushFromTexture( nullptr );
			Dest->ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );
			Dest->ItemQuantity->SetText( QuantityText );
			Dest->ItemReference = nullptr;

			return true;
		}
	}

	if (const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>( InOperation ))
	{
		if (UItemBase* ItemBase = ItemDragDrop->GetSourceItem())
		{
			if (ItemBase == this->ItemReference || ItemBase->GetItemType() != EItemType::Consumable)
				return false;

			UTexture2D* Icon = ItemBase->GetAssetData().Icon;

			const FText& QuantityText = FText::FromString( FString::FromInt(
				ItemBase->GetOwningInventory()->FindItemQuantity( ItemBase->GetTextData().Name.ToString() ) ) );

			ItemIcon->SetBrushFromTexture(Icon);
			ItemQuantity->SetVisibility( ESlateVisibility::Visible );
			ItemQuantity->SetText(QuantityText);
			ItemReference = ItemBase;

			return true;
		}
	}

	return false;
}

void UQuickSlotWidget::HorveredQuickSlotUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->SetInputMode( FInputModeUIOnly() );
		}
	}
}

void UQuickSlotWidget::UnHorveredQuickSlotUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			PC->SetInputMode( FInputModeGameOnly() );
		}
	}
}

void UQuickSlotWidget::UseItem()
{
	if(ItemReference)
	{
		if(ItemReference->GetQuantity() > 0)
		{
			if(UInventoryComponent* InventoryComponent = ItemReference->GetOwningInventory())
			{
				if(UItemBase* ItemBase = InventoryComponent->FindMatchItem( ItemReference->GetID().ToString() ))
				{
					if (ItemBase)
					{
						const FString& ItemID = ItemReference->GetID().ToString();

						ItemBase->Use();
						InventoryComponent->HandelRemoveItem( ItemReference->GetTextData().Name.ToString(), 1, true);

						if(!ItemReference->GetQuantity())
							ItemReference = InventoryComponent->FindMatchItem( ItemID );
					}
				}
			}
		}
	}
}

void UQuickSlotWidget::SetQuantity(FString ItemID, int32 NewQuantity) const
{
	if(!ItemReference) return;
	if(ItemReference->GetTextData().Name.ToString() != ItemID) return;

	ItemQuantity->SetText(FText::FromString(FString::FromInt(NewQuantity)));
}
