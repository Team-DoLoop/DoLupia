// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSpawnManager.h"
#include "Components/CapsuleComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMonsterSpawnManager::AMonsterSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnInterval = 5.0f;

	gm = nullptr;
}

// Called when the game starts or when spawned
void AMonsterSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	StartSpawnMonster = false;

	// 스포너에 태그 네임 지정
	//Tags.Add( FName( SpawnerQuestID ) );

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	if (gm)
	{
		gm->OnNextSpawnerQuestTagReceived.AddDynamic( this , &AMonsterSpawnManager::OnNextSpawnerQuestTagReceived );
		gm->OnNextSpawnerQuestTagCompleted.AddDynamic( this , &AMonsterSpawnManager::OnNextSpawnerQuestTagCompleted );
	}

	UE_LOG( LogTemp , Log , TEXT( "MonsterSpawnManager initialized with OwnQuestTag: %s" ) , *OwnQuestTag.ToString() );
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

void AMonsterSpawnManager::OnNextSpawnerQuestTagReceived(FString NextQuestTag)
{
	if (OwnQuestTag.ToString() == NextQuestTag)
	{
		UpdateSpawnerStatus();
	}
}

void AMonsterSpawnManager::OnNextSpawnerQuestTagCompleted()
{
	DeactiveMonsterSpawner();
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

void AMonsterSpawnManager::UpdateSpawnerStatus()
{
	if (gm && gm->GetNxtQuestTag() != "")
	{
		if (OwnQuestTag == FName( gm->GetNxtQuestTag() ))
		{
			// 태그 값이 일치하면 활성화 로직 추가
			ActiveMonsterSpawner();
		}

	}
}

