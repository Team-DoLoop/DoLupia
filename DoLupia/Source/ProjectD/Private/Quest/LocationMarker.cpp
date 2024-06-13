// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/LocationMarker.h"
#include <Components/BoxComponent.h>

#include "NiagaraComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "MapIconComponent.h"

// Sets default values
ALocationMarker::ALocationMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
    // 메시 컴포넌트 생성 및 부착

    locationVFX = CreateDefaultSubobject<UNiagaraComponent>( TEXT( "locationVFX" ) );
    locationVFX->SetupAttachment( BoxComponent );

	static ConstructorHelpers::FObjectFinder<UTexture2D> LocationIcon( TEXT( "/Game/Asset/Widget/MiniMap/pin.pin" ) );
	MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
	MapIcon->SetupAttachment( BoxComponent );
	// Set the player icon as texture
	MapIcon->SetIconTexture( LocationIcon.Object );
	// The icon will rotate to represent the character's rotation
	MapIcon->SetIconRotates( false );
	//MapIcon->SetIconVisible( false );
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
            locationVFX->SetVisibility( false );
			MapIcon->SetIconVisible( false );
        }
    }
}

