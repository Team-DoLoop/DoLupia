﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/LocationMarker.h"
#include <Components/BoxComponent.h>

#include "NiagaraComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "MapIconComponent.h"

// Sets default values
ALocationMarker::ALocationMarker()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
    RootComponent = BoxComponent; // BoxComponent를 루트 컴포넌트로 설정

    locationVFX = CreateDefaultSubobject<UNiagaraComponent>( TEXT( "locationVFX" ) );
    locationVFX->SetupAttachment( BoxComponent );
    locationVFX->SetVisibility( false );

    static ConstructorHelpers::FObjectFinder<UTexture2D> LocationIcon( TEXT( "/Game/Asset/Widget/MiniMap/pin.pin" ) );
    MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
    MapIcon->SetupAttachment( BoxComponent );
    // Set the player icon as texture
    if (LocationIcon.Succeeded())
    {
        MapIcon->SetIconTexture( LocationIcon.Object );
    }
    // The icon will rotate to represent the character's rotation
    MapIcon->SetIconRotates( false );
    MapIcon->SetIconVisible( false );
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
        if (player && bActiveOverlap) {
            player->OnObjectiveIDCalled.Broadcast( ObjectiveID , 1);
			MapIcon->SetIconVisible( false );
			Destroy();
        }
    }
}

void ALocationMarker::ActiveLocationMarker()
{
	locationVFX->SetVisibility( true );
	MapIcon->SetIconVisible( true );
    bActiveOverlap = true;
}



