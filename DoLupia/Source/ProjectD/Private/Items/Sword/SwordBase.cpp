﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Sword/SwordBase.h"

#include "Items/ItemBase.h"

// Sets default values
ASwordBase::ASwordBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SwordStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Static Mesh"));
	SetRootComponent(SwordStaticMesh);
}


void ASwordBase::ReceiveItemData(UItemBase* NewItemBase)
{
	ItemBase = NewItemBase;
	SwordStaticMesh->SetStaticMesh(ItemBase->GetAssetData().Mesh);
}

// Called when the game starts or when spawned
void ASwordBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwordBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

