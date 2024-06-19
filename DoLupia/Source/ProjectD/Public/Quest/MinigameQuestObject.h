// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest/StrangeObject.h"
#include "MinigameQuestObject.generated.h"

class AProjectDCharacter;
class AGrid2048;
class APlayerGameMode;
/**
 * 
 */
UCLASS()
class PROJECTD_API AMinigameQuestObject : public AStrangeObject
{
	GENERATED_BODY()

public:
	AMinigameQuestObject();

	virtual void BeginPlay() override;

	virtual FString InteractWith() override;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "MiniGame" )
	TSubclassOf<AActor> MiniGameClass;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dialog" )
	FName OwnQuestTag;

	//FString GetOwnQuestID() const;
	void ChangeMinigameColor( int32 depth );

	UFUNCTION()
	void OnNextMiniGameQuestTagReceived( FString NextQuestTag );

	UFUNCTION()
	void OnNextSpawnerQuestTagCompleted();

private:
	UPROPERTY()
	APlayerGameMode* gm;

	UPROPERTY()
	AProjectDCharacter* Player;

	UPROPERTY()
	AGrid2048* Ownminigame;

	void SpawnMiniGame();

	bool isAvailable = false;
	FString CurrentQuestTag;
	void UpdateMiniGameStatus();

	
};
