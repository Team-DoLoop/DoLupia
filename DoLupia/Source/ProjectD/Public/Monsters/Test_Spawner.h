// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "GameFramework/Actor.h"
#include "Test_Spawner.generated.h"

UCLASS()
class PROJECTD_API ATest_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
//private:
//	UPROPERTY( EditAnywhere )
//	TSubclassOf<AActor> MonsterClass;
//
//	FTimerHandle SpawnTimerHandle;
//
	void SpawnMonster();
//
	//void DestroyMonster( AMonster* Monster );
//
//	UPROPERTY( EditAnywhere )
//	bool StartSpawnMonster = false;
//
//	float currentTime = 5;
//
	FTimerHandle TimerHandle;
//==========================================================================

	class AMonster* GetPooledObject();
	void Expand();
	void ReturnObject( class AMonster* ReturnObject );

	UPROPERTY( EditAnywhere )
	TSubclassOf<class AMonster> PooledObjectClass;
	int32 PoolSize = 0;
	int32 ExpandSize = 200;

private:
	TArray< AMonster*> Pool;
};
