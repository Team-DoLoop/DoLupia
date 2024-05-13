// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Sword/SwordBase.h"

#include "Components/CapsuleComponent.h"
#include "Items/ItemBase.h"
#include "Monsters/Monster.h"

// Sets default values
ASwordBase::ASwordBase()
{
	PrimaryActorTick.bCanEverTick = false;

	
	// Collision
	ItemStaticMesh->SetCollisionProfileName("NoCollision");

	collisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("collisionComp"));
	collisionComp->SetupAttachment(RootComponent);
	collisionComp->SetGenerateOverlapEvents(true);
	collisionComp->SetCollisionProfileName(TEXT("Sword"));
	collisionComp->SetRelativeLocation(FVector(0,0, 390));
	collisionComp->SetCapsuleHalfHeight(80.0f);
	collisionComp->SetCapsuleRadius(40.0f);
}

// Called when the game starts or when spawned
void ASwordBase::BeginPlay()
{
	Super::BeginPlay();

	CollisionOff();
}

void ASwordBase::CollisionOn()
{
	SetActorEnableCollision(true);
}

void ASwordBase::CollisionOff()
{
	SetActorEnableCollision(false);
}


