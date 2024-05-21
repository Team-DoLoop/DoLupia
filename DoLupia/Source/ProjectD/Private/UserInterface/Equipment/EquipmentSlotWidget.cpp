// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Equipment/EquipmentSlotWidget.h"

#include "Components/Button.h"
#include "UserInterface/Equipment/EquipmentTooltip.h"
#include "Components/Image.h"
#include "Items/ItemBase.h"

void UEquipmentSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (TooltipFactory)
		Tooltip = CreateWidget<UEquipmentTooltip>( this , TooltipFactory );

}

void UEquipmentSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HorveredButton->OnHovered.AddDynamic( this , &UEquipmentSlotWidget::VisibleTooltip);
	HorveredButton->OnUnhovered.AddDynamic(this, &UEquipmentSlotWidget::UnVisibleTooltip );
}

void UEquipmentSlotWidget::VisibleTooltip()
{
	if(ItemReference)
	{
		Tooltip->SetupTooltip( ItemReference );
		SetToolTip( Tooltip );
		Tooltip->SetVisibility( ESlateVisibility::HitTestInvisible );
	}
	
}

void UEquipmentSlotWidget::UnVisibleTooltip()
{
	SetToolTip( nullptr );
	Tooltip->SetVisibility(ESlateVisibility::Collapsed);
}


void UEquipmentSlotWidget::SetItem(UItemBase* ItemBase)
{
	ItemReference = ItemBase;
	ItemIcon->SetBrushFromTexture( ItemReference->GetAssetData().Icon );
}



