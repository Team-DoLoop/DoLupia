// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/EquipItemBase.h"
#include "Items/ItemBase.h"

AEquipItemBase::AEquipItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Sword Static Mesh" ) );
	SetRootComponent( ItemStaticMesh );
}

void AEquipItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipItemBase::ReceiveItemData( UItemBase* NewItemBase )
{
	ItemBase = NewItemBase;
	OriginalMesh = ItemBase->GetAssetData().Mesh;

	if(!USeAvatar)
		ItemStaticMesh->SetStaticMesh( OriginalMesh );
}

void AEquipItemBase::ChangeAvatar( UStaticMesh* ItemMesh )
{
	ItemStaticMesh->SetStaticMesh( ItemMesh );
	USeAvatar = true;
}

void AEquipItemBase::UnUsedAvatar()
{
	ItemStaticMesh->SetStaticMesh( OriginalMesh );
	USeAvatar = false;
}



