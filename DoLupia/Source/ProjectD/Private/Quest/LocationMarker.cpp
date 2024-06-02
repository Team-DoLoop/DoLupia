// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/LocationMarker.h"
#include <Components/BoxComponent.h>
#include "Characters/ProjectDCharacter.h"


// Sets default values
ALocationMarker::ALocationMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );

}

// Called when the game starts or when spawned
void ALocationMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocationMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocationMarker::NotifyActorBeginOverlap( AActor* OtherActor )
{
    if (OtherActor) {
        AProjectDCharacter* player = Cast<AProjectDCharacter>( OtherActor );
        if (player) {
            player->OnObjectiveIDCalled.Broadcast( ObjectiveID , 1);
        }
    }
}

