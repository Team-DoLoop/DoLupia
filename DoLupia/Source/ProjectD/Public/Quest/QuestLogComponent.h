﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest_Base.h"
#include "Components/ActorComponent.h"
#include "QuestLogComponent.generated.h"


// 예시: FName 타입을 전달하는 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestDataLoadedSignature , FName , QuestID );

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

	UPROPERTY()
	TArray<FName> CurrentActiveQuests;

	UPROPERTY()
	TArray<FName> CompletedQuests;

	UPROPERTY()
	FName CurrentTrackedQuest;

	UPROPERTY()
	TArray<AQuest_Base*> CurrentQuest;

	UFUNCTION()
	void AddNewQuest(FName QuestID);

	//UFUNCTION()
	//void CompleteQuest(); 보상줄때 쓸 함수

	UFUNCTION()
	bool QueryActiveQuest(FName QuestID);

	//UFUNCTION()
	//void TrackQuest();
};
