// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"
#include "UserInterface/PlayerDefaults/QuickSlotDragDropOperation.h"
#include "UserInterface/PlayerDefaults/DragQuickSlotVisual.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	QuantityCalled.BindUObject(this, &UQuickSlotWidget::SetQuantity);
	PlayerController = GetWorld()->GetFirstPlayerController();
}

FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown( InGeometry , InMouseEvent );

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		DraggingQuickSlotUI();
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

	MouseUpQuickSlotUI();
	
	return false;
}


void UQuickSlotWidget::HorveredQuickSlotUI()
{
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		PlayerController->SetInputMode( InputMode );
		Hovered = true;
	}
}

void UQuickSlotWidget::UnHorveredQuickSlotUI( bool IsInputModeGameOnly )
{
	Hovered = false;

	if(!IsInputModeGameOnly)
		return;

	if (!MainQuickSlotWidget->IsDraggingWidget() && !Clicked)
	{
		if (PlayerController)
		{
			FInputModeGameOnly InputMode;
			InputMode.SetConsumeCaptureMouseDown(true);
			PlayerController->SetInputMode( InputMode );
		}
	}
}

void UQuickSlotWidget::DraggingQuickSlotUI()
{
	Clicked = true;

}

void UQuickSlotWidget::MouseUpQuickSlotUI()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer( TimerHandle , this , &UQuickSlotWidget::TimerSwapQuickSlot , 0.01f);
}



bool UQuickSlotWidget::IsHoveredButton() const
{
	return Hovered || Clicked;
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

bool UQuickSlotWidget::HandleQuickSlot( UQuickSlotWidget* OtherQuickSlot )
{
	return SwapQuickSlot( OtherQuickSlot );
}

void UQuickSlotWidget::ReleaseQuickSlot(UQuickSlotWidget* ReleasedQuickSlot ) const
{
	ReleasedQuickSlot->ItemIcon->SetBrushFromTexture( nullptr );
	ReleasedQuickSlot->ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );
	ReleasedQuickSlot->ItemQuantity->SetText( FText::FromString(""));
	ReleasedQuickSlot->ItemReference = nullptr;
}

bool UQuickSlotWidget::CheckHorveredQuickSlotUI(const FVector2D& MousePosition)
{
	const FGeometry& MyGeometry = GetCachedGeometry();

	FVector2D MySize = GetDesiredSize();
	FVector2D PixelPosition;
	FVector2D ViewPortPosition;

	if (GetWorld()->GetFirstPlayerController()->GetInputKeyTimeDown( FKey( "F11" ) ))
	{
		IsFullScreen = !IsFullScreen;
	}

	if(GEngine)
	{
		if(IsFullScreen)
		{
			PixelPosition = FVector2D( MyGeometry.AbsolutePosition );
		}
		else
		{
			USlateBlueprintLibrary::LocalToViewport( GetWorld() , MyGeometry , FVector2D( 0.0, 0.0 ) , PixelPosition , ViewPortPosition );
		}
	}
	
	if (MousePosition.X > PixelPosition.X && MousePosition.Y > PixelPosition.Y &&
	MousePosition.X < MySize.X + PixelPosition.X && MousePosition.Y < MySize.Y + PixelPosition.Y)
	{
	/*	UE_LOG( LogTemp , Warning , TEXT( "MousePosition -> x : %f, y : %f" ) , MousePosition.X , MousePosition.Y );
		UE_LOG( LogTemp , Warning , TEXT( "Size Min -> x : %f, y : %f" ) , ViewPortPosition.X , ViewPortPosition.Y );
		UE_LOG( LogTemp , Warning , TEXT( "Size Max -> x : %f, y : %f" ) , MySize.X / 2.0 + FVector2D( MyGeometry.AbsolutePosition ).X , MySize.Y / 2.0 + FVector2D( MyGeometry.AbsolutePosition ).Y );*/
		if (!Hovered)
			HorveredQuickSlotUI();

		return true;
	}

	if(IsHoveredButton())
		UnHorveredQuickSlotUI(false);

	return false;

}


void UQuickSlotWidget::SetQuantity(FString ItemID, int32 NewQuantity) const
{
	if(!ItemReference) return;
	if(ItemReference->GetTextData().Name.ToString() != ItemID) return;

	ItemQuantity->SetText(FText::FromString(FString::FromInt(NewQuantity)));
}

bool UQuickSlotWidget::SwapQuickSlot( UQuickSlotWidget* OtherQuickSlot )
{
	if (UItemBase* ItemBase = OtherQuickSlot->ItemReference)
	{
		if (ItemBase == this->ItemReference)
			return true;

		const FText& QuantityText = FText::FromString( FString::FromInt(
			ItemBase->GetOwningInventory()->FindItemQuantity( ItemBase->GetTextData().Name.ToString() ) ) );

		ItemIcon->SetBrushFromTexture( ItemBase->GetAssetData().Icon );
		ItemQuantity->SetVisibility( ESlateVisibility::Visible );
		ItemQuantity->SetText( QuantityText );
		ItemReference = ItemBase;

		OtherQuickSlot->ItemIcon->SetBrushFromTexture( nullptr );
		OtherQuickSlot->ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );
		OtherQuickSlot->ItemQuantity->SetText( QuantityText );
		OtherQuickSlot->ItemReference = nullptr;

		return true;
	}

	return false;
}

void UQuickSlotWidget::TimerSwapQuickSlot()
{
	MainQuickSlotWidget->SwapQuickSlot(this);
	Clicked = false;
}
