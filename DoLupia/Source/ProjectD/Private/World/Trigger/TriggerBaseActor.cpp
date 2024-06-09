﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/TriggerBaseActor.h"
#include "NiagaraComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "World/Trigger/TriggerType.h"


// Sets default values
ATriggerBaseActor::ATriggerBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	triggerComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "triggerComp" ) );
	this->SetRootComponent( triggerComp );

	locationVFX = CreateDefaultSubobject<UNiagaraComponent>( TEXT( "locationVFX" ) );
	locationVFX->SetupAttachment( RootComponent );

	gm = nullptr;
	LvName = "";

	// Default TriggerType
	triggerType = EPlayerTriggerType::None;


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

	AProjectDCharacter* player = Cast<AProjectDCharacter>(OtherActor);

	if(player)
	{

		if (triggerType == EPlayerTriggerType::LevelTransition)
		{
			CallLevel( LvName , player );
		} else if (triggerType == EPlayerTriggerType::CameraAngle)
		{
			ChangeCameraAngle( 90.0f );
		}
	}

}

void ATriggerBaseActor::CallLevel( FName Lvname , AProjectDCharacter* Character )
{
	gm->ChangeNextLv( Lvname, Character );
}

void ATriggerBaseActor::ChangeCameraAngle(float angle)
{
	// Player Load
	auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	// 플레이어 카메라 붐...
	FRotator NewRotation = player->CameraBoom->GetRelativeRotation();
	NewRotation.Yaw = angle;
	player->CameraBoom->SetRelativeRotation( NewRotation );
}

