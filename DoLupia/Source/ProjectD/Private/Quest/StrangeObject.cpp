// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/StrangeObject.h"

// Sets default values
AStrangeObject::AStrangeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStrangeObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AStrangeObject::InteractWith()
{
	//QuestData 에 있는 Objective ID와 같아야함.
	return FString("StrangeObject");
}

