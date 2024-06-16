// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/DestructableWallActor.h"

#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Pooling/SoundManager.h"

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
	// 벽폭발음
	ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( ExplosionSFX , ENPCSound::NPCSound2 , 0.1f );

	UE_LOG( LogTemp , Error , TEXT( "destroy Walls" )  );

	// 부숴지는 효과
	DestructableWallComp->SetSimulatePhysics( true );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

