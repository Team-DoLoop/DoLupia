// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSpawnManager.h"
#include "Components/CapsuleComponent.h"


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

	// 스포너에 태그 네임 지정
	Tags.Add( FName( SpawnerQuestID ) );
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

void AMonsterSpawnManager::DeactiveMonsterSpawner()
{
	UE_LOG( LogTemp , Warning , TEXT( "DeactiveMonsterSpawner" ) )
	StartSpawnMonster = false;
	currentTime = 0;
}

void AMonsterSpawnManager::ActiveMonsterSpawner()
{
	UE_LOG(LogTemp, Warning, TEXT("ActiveMonsterSpawner"))
	StartSpawnMonster = true;
}

void AMonsterSpawnManager::SpawnMonster()
{
	if (MonsterClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AStrikeMonster* monster = Cast<AStrikeMonster>(GetWorld()->SpawnActor<AActor>( MonsterClass , GetActorLocation() , GetActorRotation() , SpawnParams ));
	}
}

