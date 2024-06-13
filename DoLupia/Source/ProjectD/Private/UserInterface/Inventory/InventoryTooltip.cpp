// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryTooltip.h"

#include "Components/TextBlock.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Items/ItemBase.h"


void UInventoryTooltip::SetupTooltip()
{
	UItemBase* ItemBeingHovered = InventoryItemSlotBeingHovered->GetItemReference();

	switch (const EItemType& MyItemType = ItemBeingHovered->GetItemType())
	{
	case EItemType::Head:
		ItemType->SetText( FText::FromString( L"머리" ) );
	case EItemType::Top:
		ItemType->SetText( FText::FromString( L"상의" ) );
	case EItemType::Pants:
		ItemType->SetText( FText::FromString( L"하의" ) );
	case EItemType::Shoes:
		ItemType->SetText( FText::FromString( L"신발" ) );
		
		break;
	case EItemType::Weapon:
		ItemType->SetText(FText::FromString(L"무기"));
		break;
	case EItemType::Shield:
		ItemType->SetText(FText::FromString(L"방패"));
		break;
	case EItemType::Spell:
		ItemType->SetText(FText::FromString(L"보조무기"));
		break;
	case EItemType::Consumable:
		ItemType->SetText( FText::FromString( L"소비" ) );
		DamageValue->SetVisibility( ESlateVisibility::Collapsed );
		ArmorRating->SetVisibility( ESlateVisibility::Collapsed );
		SellValue->SetVisibility( ESlateVisibility::Collapsed );

		break;
	case EItemType::Quest:
		break;
	case EItemType::Mundane:
		ItemType->SetText( FText::FromString( L"기타" ) );
		DamageValue->SetVisibility( ESlateVisibility::Collapsed );
		ArmorRating->SetVisibility( ESlateVisibility::Collapsed );
		UsageText->SetVisibility( ESlateVisibility::Collapsed );
		SellValue->SetVisibility( ESlateVisibility::Collapsed );
		break;
	default:;
	}

	switch (ItemBeingHovered->GetItemQuality())
	{
	case EItemQuality::Shoddy:
		ItemQuality->SetText( FText::FromString( L"일반" ) );
		break;
	case EItemQuality::Common:
		ItemQuality->SetText( FText::FromString( L"고급" ) );
		break;
	case EItemQuality::Quality:
		ItemQuality->SetText( FText::FromString( L"희귀" ) );
		break;
	case EItemQuality::Masterwork:
		ItemQuality->SetText( FText::FromString( L"전설" ) );
		break;
	case EItemQuality::Grandmaster:
		ItemQuality->SetText( FText::FromString( L"유물" ) );
		break;
	}


	const FItemTextData& TextData = ItemBeingHovered->GetTextData();
	const FItemStatistics& ItemStatistics = ItemBeingHovered->GetItemStatistics();
	const FItemNumericData& NumericData = ItemBeingHovered->GetNumericData();

	ItemName->SetText( TextData.Name );
	DamageValue->SetText( FText::AsNumber( ItemStatistics.DamageValue ) );
	ArmorRating->SetText( FText::AsNumber( ItemStatistics.ArmorRating ) );
	UsageText->SetText( TextData.UsageText );
	ItemDescription->SetText( TextData.Description );
	SellValue->SetText( FText::AsNumber( ItemStatistics.SellValue ) );

	float Weight = NumericData.bIsStackable
		? ItemBeingHovered->GetItemStackWeight()
		: ItemBeingHovered->GetItemSingleWeight();

	const FString& WeightInfo = FString::Printf( TEXT( "무게 : %.2f" ) , Weight );

	StackWeight->SetText( FText::FromString( WeightInfo ) );

	if (NumericData.bIsStackable)
	{
		const FString& StackInfo = FString::Printf( TEXT( "아이템 최대 소유량 : %d" ) , NumericData.MaxStackSize );
		MaxStackSize->SetText( FText::FromString( StackInfo ) );
	}
	else
	{
		MaxStackSize->SetVisibility( ESlateVisibility::Collapsed );
	}
}
