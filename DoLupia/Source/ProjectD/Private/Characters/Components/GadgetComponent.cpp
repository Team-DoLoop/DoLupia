// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/GadgetComponent.h"

#include "Characters/ProjectDCharacter.h"
#include "Data/ItemDataStructs.h"
#include "Items/EquipItemBase.h"
#include "Items/ItemBase.h"
#include "Items/Clothes_Head/Clothes_HeadBase.h"
#include "Items/Clothes_Pants/Clothes_PantsBase.h"
#include "Items/Clothes_Shoes/Clothes_ShoesBase.h"
#include "Items/Clothes_Top/Clothes_TopBase.h"
#include "Items/Sword/SwordBase.h"


UGadgetComponent::UGadgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UGadgetComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGadgetComponent::InitEquip()
{
	AProjectDCharacter* Character = Cast<AProjectDCharacter>( GetOwner() );
	// GlovesSocket

	// Head
	const FName& HeadSocket( TEXT( "FX_Head" ) );
	HeadBase = Character->GetWorld()->SpawnActor<AClothes_HeadBase>( FVector::ZeroVector , FRotator::ZeroRotator );

	if (HeadBase)
	{
		HeadBase->AttachToComponent( Character->GetMesh() ,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale , HeadSocket );
	}

	// Top
	const FName& TopSocket( TEXT( "Chest" ) );
	TopBase = Character->GetWorld()->SpawnActor<AClothes_TopBase>( FVector::ZeroVector , FRotator::ZeroRotator );

	if (TopBase)
	{
		TopBase->AttachToComponent( Character->GetMesh() ,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale , TopSocket );
	}

	// Pants
	const FName& PantsSocket( TEXT( "PantsSocket" ) );
	PantsBase = Character->GetWorld()->SpawnActor<AClothes_PantsBase>( FVector::ZeroVector , FRotator::ZeroRotator );

	if (PantsBase)
	{
		PantsBase->AttachToComponent( Character->GetMesh() ,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale , PantsSocket );
	}

	// Shoes
	const FName& ShoesSocket( TEXT( "Foot_R" ) );
	ShoesBase = Character->GetWorld()->SpawnActor<AClothes_ShoesBase>( FVector::ZeroVector , FRotator::ZeroRotator );

	if (ShoesBase)
	{
		ShoesBase->AttachToComponent( Character->GetMesh() ,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale , ShoesSocket );
	}

	// Sword
	const FName& SwordSocket( TEXT( "SwordSocket" ) );
	SwordBase = Character->GetWorld()->SpawnActor<ASwordBase>( FVector::ZeroVector , FRotator::ZeroRotator );

	if (SwordBase)
	{
		SwordBase->AttachToComponent( Character->GetMesh() ,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale , SwordSocket );
	}
}

// Called every frame
void UGadgetComponent::TickComponent( float DeltaTime , ELevelTick TickType , FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime , TickType , ThisTickFunction );

	// ...
}

UItemBase* UGadgetComponent::ChangeItem(UItemBase* ItemBase) const
{
	TObjectPtr<UItemBase> EquippedItem = nullptr;

	switch (EItemType ItemType = ItemBase->GetItemType())
	{

	case EItemType::Head:
		if(HeadBase)
		{
			EquippedItem = HeadBase->GetItemBase();
			HeadBase->ReceiveItemData( ItemBase );
		}
		break;
	case EItemType::Top:
		if (TopBase)
		{
			EquippedItem = TopBase->GetItemBase();
			TopBase->ReceiveItemData( ItemBase );
		}
		break;
	case EItemType::Pants:
		if (PantsBase)
		{
			EquippedItem = PantsBase->GetItemBase();
			PantsBase->ReceiveItemData( ItemBase );
		}
		break;
	case EItemType::Shoes:
		if (ShoesBase)
		{
			EquippedItem = ShoesBase->GetItemBase();
			ShoesBase->ReceiveItemData( ItemBase );
		}
		break;
	case EItemType::Weapon:
		if (SwordBase)
		{
			EquippedItem = SwordBase->GetItemBase();
			SwordBase->ReceiveItemData( ItemBase );
		}
		break;
	case EItemType::Spell:

		break;
	default: ;

	}

	return EquippedItem;

}







