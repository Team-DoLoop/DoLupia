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

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AMonsterSpawnManager::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	StartSpawnMonster = false;

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	if (gm)
	{
		gm->OnNextSpawnerQuestTagReceived.AddDynamic( this , &AMonsterSpawnManager::OnNextSpawnerQuestTagReceived );
		gm->OnNextSpawnerQuestTagCompleted.AddDynamic( this , &AMonsterSpawnManager::OnNextSpawnerQuestTagCompleted );
	}

	UE_LOG( LogTemp , Log , TEXT( "MonsterSpawnManager initialized with OwnQuestTag: %s" ) , *OwnQuestTag.ToString() );

	FFileHelper::SaveStringToFile( L"AMonsterSpawnManager::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
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

