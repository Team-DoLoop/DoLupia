// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "Data/WidgetData.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"


void UPlayerDefaultsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(QuickSlotFactory)
	{
		QuickSlot = CreateWidget<UMainQuickSlotWidget>(GetWorld(), QuickSlotFactory );
		QuickSlot->AddToViewport( static_cast<uint32>(ViewPortPriority::Main) );
	}
	
	if(PlayerBattleUIFactory)
	{
		PlayerBattleUI = CreateWidget<UPlayerBattleWidget>(GetWorld(), PlayerBattleUIFactory);
		PlayerBattleUI->AddToViewport( static_cast<uint32>(ViewPortPriority::Main) );
	}

	SetIsFocusable( true );
	
}

void UPlayerDefaultsWidget::UseQuickSlot(int32 SlotNumber)
{
	FindQuickSlot(SlotNumber)->UseItem();
}

void UPlayerDefaultsWidget::RefreshQuickSlot(const FString& ItemName, int32 NewQuantity) const
{
	QuickSlot->GetQuickSlotWidget1()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget2()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget3()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget4()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget5()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget6()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget7()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget8()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget9()->QuantityCalled.Execute( ItemName , NewQuantity );
	QuickSlot->GetQuickSlotWidget0()->QuantityCalled.Execute( ItemName , NewQuantity );
}

UQuickSlotWidget* UPlayerDefaultsWidget::FindQuickSlot( int32 FindIndex )
{
	if (FindIndex == 0)	return QuickSlot->GetQuickSlotWidget1();
	if (FindIndex == 1)	return QuickSlot->GetQuickSlotWidget2();
	if (FindIndex == 2)	return QuickSlot->GetQuickSlotWidget3();
	if (FindIndex == 3)	return QuickSlot->GetQuickSlotWidget4();
	if (FindIndex == 4)	return QuickSlot->GetQuickSlotWidget5();
	if (FindIndex == 5) return QuickSlot->GetQuickSlotWidget6();
	if (FindIndex == 6) return QuickSlot->GetQuickSlotWidget7();
	if (FindIndex == 7) return QuickSlot->GetQuickSlotWidget8();
	if (FindIndex == 8) return QuickSlot->GetQuickSlotWidget9();
	if (FindIndex == 9) return QuickSlot->GetQuickSlotWidget0();

	check( false );
	return nullptr;
}

void UPlayerDefaultsWidget::UpdateMouseWidget(FVector2D MousePosition) const
{
	if (QuickSlot)
		QuickSlot->UpdateMouseWidget( MousePosition );

}
