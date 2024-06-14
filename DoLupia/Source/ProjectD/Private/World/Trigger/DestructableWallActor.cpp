// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/DestructableWallActor.h"

#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ADestructableWallActor::ADestructableWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestructableWallComp = CreateDefaultSubobject<UGeometryCollectionComponent>( TEXT( "DestructableWallComp" ) );
	RootComponent = DestructableWallComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	BoxComp->SetupAttachment( RootComponent );

	DestructableWallComp->SetSimulatePhysics( false );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
}

// Called when the game starts or when spawned
void ADestructableWallActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestructableWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableWallActor::ExplosionWalls()
{
	DestructableWallComp->SetSimulatePhysics( true );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

