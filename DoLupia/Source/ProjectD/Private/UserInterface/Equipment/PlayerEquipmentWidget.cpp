// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Equipment/PlayerEquipmentWidget.h"
#include "Data/ItemDataStructs.h"
#include "Items/ItemBase.h"
#include "UserInterface/Equipment/EquipmentSlotWidget.h"


void UPlayerEquipmentWidget::UpdateWidget(UItemBase* ItemBase) const
{
	if(!ItemBase)
	{
		UE_LOG(LogTemp, Error, TEXT("Update Widget -> ItemBase is nullptr"));
		return;
	}

	UTexture2D* Icon = ItemBase->GetAssetData().Icon;

	switch (ItemBase->GetItemType())
	{
		case EItemType::Head:	Head->SetItem( ItemBase );		break;
		case EItemType::Top:	Top->SetItem( ItemBase );			break;
		case EItemType::Pants:	Pants->SetItem( ItemBase );		break;
		case EItemType::Shoes:	Shoes->SetItem( ItemBase );		break;
		case EItemType::Weapon:	Weapon->SetItem( ItemBase );		break;
		default: ;
	}
}
