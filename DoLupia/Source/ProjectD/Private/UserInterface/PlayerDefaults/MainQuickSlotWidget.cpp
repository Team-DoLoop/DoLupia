// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"

#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"

void UMainQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuickSlot1->SetIndex( 0 );
	QuickSlot2->SetIndex( 1 );
	QuickSlot3->SetIndex( 2 );
	QuickSlot4->SetIndex( 3 );
	QuickSlot5->SetIndex( 4 );
	QuickSlot6->SetIndex( 5 );
	QuickSlot7->SetIndex( 6 );
	QuickSlot8->SetIndex( 7 );
	QuickSlot9->SetIndex( 8 );
	QuickSlot0->SetIndex( 9 );
}
