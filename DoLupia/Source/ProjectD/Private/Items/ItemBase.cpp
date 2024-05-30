﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"

#include "Characters/PlayerStat.h"
#include "Characters/ProjectDCharacter.h"
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
	this->SkillAttribute = MyItemBase->SkillAttribute;
	this->bIsCopy = true;
	this->bIsPickup = true;
}

void UItemBase::SetQuantity(const int32 NewQuantity, bool IsRemoveItem)
{
	if(NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, this->NumericData.bIsStackable ? NewQuantity : 1);

		if(OwningInventory)
		{
			if(Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this,IsRemoveItem);
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
	if (Character)
	{
		if (APlayerStat* PlayerStat = Character->GetPlayerStat())
		{
			PlayerStat->AddSkillLevelMelee( ItemStatistics.SkillPointMelee );
			PlayerStat->AddSkillLevelRange( ItemStatistics.SkillPointRange );
			PlayerStat->SetHP( PlayerStat->GetHP() + ItemStatistics.HealthValue );
			PlayerStat->SetMP( PlayerStat->GetHP() + ItemStatistics.HealthValue );
		}
	}	
}

