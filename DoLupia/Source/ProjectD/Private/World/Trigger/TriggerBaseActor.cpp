// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/TriggerBaseActor.h"
#include "NiagaraComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/BoxComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATriggerBaseActor::ATriggerBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "triggerComp" ) );
	this->SetRootComponent( triggerComp );

	locationVFX = CreateDefaultSubobject<UNiagaraComponent>( TEXT( "locationVFX" ) );
	locationVFX->SetupAttachment( RootComponent );

	gm = nullptr;
	LvName = "";

}

// Called when the game starts or when spawned
void ATriggerBaseActor::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
}

// Called every frame
void ATriggerBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerBaseActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	auto player = Cast<AProjectDCharacter>(OtherActor);

	if(player)
	{
		CallLevel( LvName );
	}

}

void ATriggerBaseActor::CallLevel(FName Lvname)
{
	gm->ChangeNextLv( Lvname );
}

