// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/ConcreteBarrier.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Gamemode/PlayerGameMode.h>


// Sets default values
AConcreteBarrier::AConcreteBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
	RootComponent = BoxComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComponent" ) );
	MeshComponent->SetupAttachment( BoxComponent );

	this->SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void AConcreteBarrier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConcreteBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConcreteBarrier::BarrierRelease( bool onoff )
{
	if (!onoff) 
	{
		UE_LOG(LogTemp,Error,TEXT("BarrierRelease"))
		this->SetActorEnableCollision( false );
		this->Destroy();
	}
}

