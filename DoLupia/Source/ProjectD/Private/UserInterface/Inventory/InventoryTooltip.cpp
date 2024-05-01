// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryTooltip.h"

#include "Components/TextBlock.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Items/ItemBase.h"

void UInventoryTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	const UItemBase* ItemBeingHovered = InventoryItemSlotBeingHovered->GetItemReference();

	switch (ItemBeingHovered->GetItemType())
	{
	case EItemType::Armor: 
		break;
	case EItemType::Weapon:
		break;
	case EItemType::Shield: 
		break;
	case EItemType::Spell: 
		break;
	case EItemType::Consumable:
		ItemType->SetText(FText::FromString("Consumable"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		SellValue->SetVisibility(ESlateVisibility::Collapsed);

		break;
	case EItemType::Quest: 
		break;
	case EItemType::Mundane:
		ItemType->SetText(FText::FromString("Consumable"));
		DamageValue->SetVisibility(ESlateVisibility::Collapsed);
		ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
		UsageText->SetVisibility(ESlateVisibility::Collapsed);
		SellValue->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default: ;
	}

	const FItemTextData& TextData = ItemBeingHovered->GetTextData();
	const FItemStatistics& ItemStatistics = ItemBeingHovered->GetItemStatistics();
	const FItemNumericData& NumericData = InventoryItemSlotBeingHovered->GetItemReference()->GetNumericData();

	ItemName->SetText(TextData.Name);
	DamageValue->SetText(FText::AsNumber(ItemStatistics.DamageValue));
	ArmorRating->SetText(FText::AsNumber(ItemStatistics.ArmorRating));
	UsageText->SetText(TextData.UsageText);
	ItemDescription->SetText(TextData.Description);
	SellValue->SetText(FText::AsNumber(ItemStatistics.SellValue));
	StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));

	if(NumericData.bIsStackable)
	{
		MaxStackSize->SetText(FText::AsNumber(NumericData.MaxStackSize));
	}
	else
	{
		MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
	}
}
