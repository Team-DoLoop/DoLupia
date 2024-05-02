// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UQuestLogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestLogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY()
	TArray<FString> CurrentActiveQuests;

	UPROPERTY()
	TArray<FString> CompletedQuests;

	UPROPERTY()
	FString CurrentTrackedQuest;

	UPROPERTY()
	TArray<AQuest_Base*> CurrentQuest;

	UFUNCTION()
	void AddNewQuest(FString QuestID);

	//UFUNCTION()
	//void CompleteQuest(); 보상줄때 쓸 함수

	UFUNCTION()
	bool QueryActiveQuest(FString QuestID);

	//UFUNCTION()
	//void TrackQuest();
};
