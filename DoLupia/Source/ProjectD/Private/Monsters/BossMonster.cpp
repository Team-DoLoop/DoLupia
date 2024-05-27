// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossMonster.h"
#include "Monsters/MonsterAIController.h"
#include "Engine/World.h"  // 필요
#include "CollisionQueryParams.h"  // 필요
#include "Engine/EngineTypes.h"  // 필요
#include "Engine/Engine.h"  // GEngine
#include "Engine/OverlapResult.h"

// Sets default values
ABossMonster::ABossMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}


// Called when the game starts or when spawned
void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

