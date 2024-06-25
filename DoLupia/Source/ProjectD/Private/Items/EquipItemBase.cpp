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

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AEquipItemBase::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

void AEquipItemBase::ReceiveItemData( UItemBase* NewItemBase , bool UsedSubMesh )
{
	ItemBase = NewItemBase;

	!UsedSubMesh
		? OriginalMesh = ItemBase->GetAssetData().Mesh
		: OriginalMesh = ItemBase->GetAssetData().SubMesh;

	if(!USeAvatar)
	{
		if(OriginalMesh)
			ItemStaticMesh->SetStaticMesh( OriginalMesh );
	}
		
}

void AEquipItemBase::ChangeAvatar( UStaticMesh* ItemMesh )
{
	ItemStaticMesh->SetStaticMesh( ItemMesh );
	USeAvatar = true;
}

void AEquipItemBase::UnUsedAvatar()
{
	if(OriginalMesh)
		ItemStaticMesh->SetStaticMesh( OriginalMesh );

	USeAvatar = false;
}



