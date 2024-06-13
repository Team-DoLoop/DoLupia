// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Struct_QuestSystem.generated.h"

enum class EExplainType : uint8;

UENUM( BlueprintType )
enum class EObjectiveType : uint8
{
	Location ,
	Kill ,
	Interaction ,
	Collect ,
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
	virtual void Tick( float DeltaTime ) override;

};

USTRUCT( Atomic , BlueprintType )
struct FRewardsDetails
{
	GENERATED_BODY()

public:

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TMap<FString , int32> RewardsItem;

};

USTRUCT( Atomic , BlueprintType )
struct FObjectiveDetails
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString ObjectiveName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString Description;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EObjectiveType Type;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString ObjectiveID;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	int32 Quantity;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TMap<FString , int32> ItemObjectives;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool IsOptional;
};

USTRUCT( Atomic , BlueprintType )
struct FStageDetails
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString StageName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString Description;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TArray<FObjectiveDetails> Objectives;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TArray<FRewardsDetails> ItemRewards;
};

USTRUCT( Atomic , BlueprintType )
struct FStoryDetails
{
	GENERATED_BODY()

	// 다음에 스토리 지문이 나오는지
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool IsAutoStory;;

	// 나온다면 어떤 유형인지
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EExplainType QuestStoryType;
};

USTRUCT( Atomic , BlueprintType )
struct FQuestDetails :public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString LogDescription;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FString TrackingDescription;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool IsMainQuest;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	TArray<FStageDetails> Stages;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool AutoAccept;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool AutoComplete;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FStoryDetails AutoStory;
};