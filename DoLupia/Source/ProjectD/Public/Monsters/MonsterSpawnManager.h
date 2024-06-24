// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrikeMonster.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnManager.generated.h"

class APlayerGameMode;

UCLASS()
class PROJECTD_API AMonsterSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dialog" )
	FName OwnQuestTag;

	UFUNCTION()
	void OnNextSpawnerQuestTagReceived( FString NextQuestTag );

	UFUNCTION()
	void OnNextSpawnerQuestTagCompleted();

	void ActiveMonsterSpawner();
	void DeactiveMonsterSpawner();

private:
	UPROPERTY( EditAnywhere  )
	TSubclassOf<AActor> MonsterClass;

	UPROPERTY( EditAnywhere )
	float SpawnInterval;

	FTimerHandle SpawnTimerHandle;

	void SpawnMonster();

	UPROPERTY( EditAnywhere )
	bool StartSpawnMonster = false;

	float currentTime = 5;

	UPROPERTY()
	APlayerGameMode* gm;

	FString CurrentQuestTag;
	void UpdateSpawnerStatus();

	//TArray< AMonster*> MonsterArr;

	void GetAllMonsters();

	FTimerHandle TimerHandle;
	
	int MonsterNum = 0;

	int MonsterMaxNum = 25;
};
