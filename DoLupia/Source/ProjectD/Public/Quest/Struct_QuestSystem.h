// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Struct_QuestSystem.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{ 
	Location,
	Kill,
	Interaction,
	Collect,
};

UCLASS()
class PROJECTD_API AStruct_QuestSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStruct_QuestSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

USTRUCT(Atomic, BlueprintType)
struct FObjectiveDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectiveType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOptional;
};

USTRUCT(Atomic, BlueprintType)
struct FStageDetails
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StageName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FObjectiveDetails> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, int32> ItemRewards;
};

USTRUCT(Atomic, BlueprintType)
struct FQuestDetails :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LogDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TrackingDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMainQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStageDetails> Stages;
};