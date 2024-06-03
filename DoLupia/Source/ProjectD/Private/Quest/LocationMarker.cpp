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
    // 메시 컴포넌트 생성 및 부착
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "Location Marker" ) );

    MeshComponent->SetupAttachment( BoxComponent );
}

// Called when the game starts or when spawned
void ALocationMarker::BeginPlay()
{
	Super::BeginPlay();
    // 메시 컴포넌트의 가시성을 초기화하여 끔
    MeshComponent->SetVisibility( true );
	
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
            // 메시 컴포넌트의 가시성을 초기화하여 끔
            MeshComponent->SetVisibility( false );
            player->OnObjectiveIDCalled.Broadcast( ObjectiveID , 1);
        }
    }
}

