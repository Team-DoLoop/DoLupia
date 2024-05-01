// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Struct_QuestSystem.h"

// Sets default values
AStruct_QuestSystem::AStruct_QuestSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStruct_QuestSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStruct_QuestSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

