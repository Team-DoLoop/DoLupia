// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"

#include "Items/ItemBase.h"
#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"

void UMainQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuickSlot1->InitQuickSlotWidget( 0, this );
	QuickSlot2->InitQuickSlotWidget( 1, this );
	QuickSlot3->InitQuickSlotWidget( 2, this );
	QuickSlot4->InitQuickSlotWidget( 3, this );
	QuickSlot5->InitQuickSlotWidget( 4, this );
	QuickSlot6->InitQuickSlotWidget( 5, this );
	QuickSlot7->InitQuickSlotWidget( 6, this );
	QuickSlot8->InitQuickSlotWidget( 7, this );
	QuickSlot9->InitQuickSlotWidget( 8, this );
	QuickSlot0->InitQuickSlotWidget( 9, this );

	QuickSlotArray.Add( QuickSlot1 );
	QuickSlotArray.Add( QuickSlot2 );
	QuickSlotArray.Add( QuickSlot3 );
	QuickSlotArray.Add( QuickSlot4 );
	QuickSlotArray.Add( QuickSlot5 );
	QuickSlotArray.Add( QuickSlot6 );
	QuickSlotArray.Add( QuickSlot7 );
	QuickSlotArray.Add( QuickSlot8 );
	QuickSlotArray.Add( QuickSlot9 );
	QuickSlotArray.Add( QuickSlot0 );

	PlayerController = GetWorld()->GetFirstPlayerController();

	SetIsFocusable( true );
}

void UMainQuickSlotWidget::SwapQuickSlot(UQuickSlotWidget* OnClickedQuickSlot)
{
	for(auto elem : QuickSlotArray)
	{
		if(elem->IsHoveredButton())
		{
			if(elem->HandleQuickSlot( OnClickedQuickSlot ))
				return;
		}
	}

	OnClickedQuickSlot->ReleaseQuickSlot( OnClickedQuickSlot );
}

bool UMainQuickSlotWidget::IsDraggingWidget()
{
	for (auto elem : QuickSlotArray)
	{
		if (elem->IsHoveredButton())
			return true;
	}

	return false;
}

bool UMainQuickSlotWidget::QuickSlotMouseHoveredWidget( const FVector2D& MousePosition )
{
	for (auto elem : QuickSlotArray)
	{
		if(elem->CheckHorveredQuickSlotUI( MousePosition ))
			return true;
	}

	return false;
}



