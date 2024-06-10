// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"


class AQuest_Base;
class UQuestTracker;

// 예시: FName 타입을 전달하는 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestDataLoadedSignature , FName , QuestID );
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateCurrentActiveQuest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestCompleted , AQuest_Base*, D_QuestActor );

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

	UPROPERTY( BlueprintAssignable )
	FQuestDataLoadedSignature OnQuestDataLoaded;

	FUpdateCurrentActiveQuest UpdateCurrentActiveQuest;

	UPROPERTY( BlueprintAssignable )
	FQuestCompleted QuestCompleted;

	UPROPERTY()
	TArray<FName> CurrentActiveQuests;

	UPROPERTY()
	TArray<FName> CompletedQuests;

	UPROPERTY()
	FName CurrentTrackedQuest;

	UPROPERTY()
	TArray<class AQuest_Base*> CurrentQuest;

	UFUNCTION()
	void AddNewQuest(FName QuestID);

	UFUNCTION()
	void CompleteQuest( FName QuestID );

	UFUNCTION()
	void TurnInQuest( FName QuestID );

	UFUNCTION()
	void AddToTracker();

	UFUNCTION()
	void RemoveTracker();

	UFUNCTION()
	bool QueryActiveQuest(FName QuestID);

	UFUNCTION()
	bool QueryCompleteQuests( FName QuestID );

	UFUNCTION()
	bool QueryCompleteQuestsTurnedIn( FName QuestID );

	UFUNCTION()
	AQuest_Base* GetQuestActor(FName QuestID);

	UFUNCTION()
	void TrackQuest( AQuest_Base* QuestActor );

	UPROPERTY( EditAnywhere )
	TSubclassOf<UQuestTracker> QuestTracker_Widget;

	UPROPERTY()
	class UQuestTracker* Tracker;

	FTimerHandle TimerHandle;

};
