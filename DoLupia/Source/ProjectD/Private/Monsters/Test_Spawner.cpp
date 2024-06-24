// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Test_Spawner.h"

#include "Monsters/Monster.h"

// Sets default values
ATest_Spawner::ATest_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATest_Spawner::BeginPlay()
{
	Super::BeginPlay();
	Expand();
	GetWorld()->GetTimerManager().SetTimer( TimerHandle , this , &ATest_Spawner::SpawnMonster , 5.0f , true );
}

void ATest_Spawner::SpawnMonster()
{
	AMonster* Monster = GetPooledObject();
	if (Monster)
	{
		//Monster->SetActive( true );
		// Additional code to set the monster's position and initialize it can be added here
	}
}

AMonster* ATest_Spawner::GetPooledObject()
{
	if (Pool.Num() == 0) Expand(); //추가
	return Pool.Pop();
}

void ATest_Spawner::Expand()
{
	for (int i = 0; i < ExpandSize; i++)
	{
		AMonster* PoolableActor = GetWorld()->SpawnActor<AMonster>( PooledObjectClass , FVector().ZeroVector , FRotator().ZeroRotator );
		//PoolableActor->SetActive( false );
		Pool.Push( PoolableActor );
	}
	//PoolSize += ExpandSize;
	//const int32 _poolsize = Pool.Num();
}

void ATest_Spawner::ReturnObject(AMonster* ReturnObject)
{
	Pool.Push( ReturnObject );
}

