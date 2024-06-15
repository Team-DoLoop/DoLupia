// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSpawnManager.h"


// Sets default values
AMonsterSpawnManager::AMonsterSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnInterval = 5.0f;
}

// Called when the game starts or when spawned
void AMonsterSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	StartSpawnMonster = false;

}

// Called every frame
void AMonsterSpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(StartSpawnMonster)
	{
		currentTime += GetWorld()->GetDeltaSeconds();
		if(currentTime>SpawnInterval)
		{
			SpawnMonster();
			currentTime = 0;
		}
	}


}

void AMonsterSpawnManager::SpawnMonster()
{
	if (MonsterClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>( MonsterClass , GetActorLocation() , GetActorRotation() , SpawnParams );
	}
}

