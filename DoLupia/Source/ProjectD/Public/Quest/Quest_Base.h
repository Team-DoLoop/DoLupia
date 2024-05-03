// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest/Struct_QuestSystem.h"
#include "Quest_Base.generated.h"

UCLASS()
class AQuest_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere) //expose on spawn 안됨
	FName QuestID;

	UPROPERTY()
	FQuestDetails QuestDetails;

	UPROPERTY()
	int32 CurrentStage;

	UPROPERTY()
	FStageDetails CurrentStageDetails;

	UPROPERTY()
	TMap<FString, int32> CurrentObjectiveProgress;

	UPROPERTY()
	bool IsCompleted;
};
