// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSpawnManager.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

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
	GetWorld()->GetTimerManager().SetTimer( TimerHandle , this , &AMonsterSpawnManager::GetAllMonsters , 1.0f , true );

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
		if (MonsterNum < MonsterMaxNum)
		{
			currentTime += GetWorld()->GetDeltaSeconds();
			if (currentTime > SpawnInterval)
			{
				SpawnMonster();
				currentTime = 0;
			}
		}
		else
		{
			
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
		UE_LOG( LogTemp , Warning , TEXT( "OnNextSpawnerQuestTagReceived - QuestTag : %s" ),*NextQuestTag )
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
		AActor* monster = Cast<AActor>(GetWorld()->SpawnActor<AActor>( MonsterClass , GetActorLocation() , GetActorRotation() , SpawnParams ));
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

void AMonsterSpawnManager::GetAllMonsters()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	TArray< AMonster*> MonsterArr;

	for (TActorIterator<AMonster> ActorItr( World ); ActorItr; ++ActorItr)
	{
		// 현재 반복 중인 액터가 AMonster 클래스의 인스턴스인 경우
		AMonster* Monster = *ActorItr;
		if (Monster)
		{
			// 몬스터 배열에 추가
			MonsterArr.Add( Monster );
		}
	}

	MonsterNum = MonsterArr.Num();
	//UE_LOG( LogTemp , Warning , TEXT( "Monster Count : %d" ) , MonsterNum );

	/*if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green ,  TEXT("%d") , MonsterNum );
	}*/

}

