// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/DestructableWallActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

// Sets default values
ADestructableWallActor::ADestructableWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestructableWallComp = CreateDefaultSubobject<UGeometryCollectionComponent>( TEXT( "DestructableWallComp" ) );
	DestructableWallComp->SetupAttachment( RootComponent );

	DestructableWallComp->SetSimulatePhysics( false );
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
	//DestructableWallComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

