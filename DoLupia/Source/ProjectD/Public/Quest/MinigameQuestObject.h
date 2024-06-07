﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/StrangeObject.h"
#include "MinigameQuestObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AMinigameQuestObject : public AStrangeObject
{
	GENERATED_BODY()

public:
	AMinigameQuestObject();

	virtual FString InteractWith() override;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "MiniGame" )
	TSubclassOf<AActor> MiniGameClass;

private:
	void SpawnMiniGame();

	
};
