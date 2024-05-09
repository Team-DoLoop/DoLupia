// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

#include "Characters/Components/InventoryComponent.h"

UItemBase::UItemBase() : bIsCopy(false), bIsPickup(false)
{
}
void UItemBase::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

void UItemBase::CreateItemCopy(const UItemBase* MyItemBase)
{
	this->ID = MyItemBase->ID;
	this->Quantity = MyItemBase->Quantity;
	this->ItemQuality = MyItemBase->ItemQuality;
	this->ItemType = MyItemBase->ItemType;
	this->TextData = MyItemBase->TextData;
	this->NumericData = MyItemBase->NumericData;
	this->ItemStatistics = MyItemBase->ItemStatistics;
	this->AssetData = MyItemBase->AssetData;
	this->bIsCopy = true;
	this->bIsPickup = true;

	// TObjectPtr<UItemBase> ItemCopy = MyItemBase;

	//ItemCopy = NewObject<UItemBase>( StaticClass() );

	//ItemCopy->ID = this->ID;
	//ItemCopy->Quantity = this->Quantity;
	//ItemCopy->ItemQuality = this->ItemQuality;
	//ItemCopy->ItemType = this->ItemType;
	//ItemCopy->TextData = this->TextData;
	//ItemCopy->NumericData = this->NumericData;
	//ItemCopy->ItemStatistics = this->ItemStatistics;
	//ItemCopy->AssetData = this->AssetData;
	//ItemCopy->bIsCopy = true;
	//ItemCopy->bIsPickup = true;

	//return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if(NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, this->NumericData.bIsStackable ? NewQuantity : 1);

		if(OwningInventory)
		{
			if(Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ItemBase OwningInventory was null!"));
		}
	}

}

void UItemBase::Use(AProjectDCharacter* Character)
{
}


