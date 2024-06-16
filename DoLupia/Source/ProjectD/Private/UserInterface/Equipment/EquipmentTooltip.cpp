// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Equipment/EquipmentTooltip.h"
#include "UserInterface/Equipment/EquipmentSlotWidget.h"
#include "Items/ItemBase.h"
#include "Components/TextBlock.h"

void UEquipmentTooltip::SetupTooltip( UItemBase* ItemBase )
{
	const FItemTextData& TextData = ItemBase->GetTextData();
	const FItemStatistics& ItemStatistics = ItemBase->GetItemStatistics();
	const FItemNumericData& NumericData = ItemBase->GetNumericData();

	ItemName->SetText( TextData.Name );

	DamageValue->SetText( FText::FromString( FString( L"공격력 : " ) + FText::AsNumber( ItemStatistics.DamageValue ).ToString() ) );
	ArmorRating->SetText( FText::FromString( FString( L"방어력 : " ) + FText::AsNumber( ItemStatistics.ArmorRating ).ToString() ) );

	UsageText->SetText( TextData.UsageText );
	ItemDescription->SetText( TextData.Description );
	SellValue->SetText( FText::AsNumber( ItemStatistics.SellValue ) );

	float Weight = NumericData.bIsStackable
		? ItemBase->GetItemStackWeight()
		: ItemBase->GetItemSingleWeight();

	const FString& WeightInfo = { "Weight : " + FString::Printf( TEXT( "%.2f" ), Weight ) };

	StackWeight->SetText( FText::FromString( WeightInfo ) );
}
