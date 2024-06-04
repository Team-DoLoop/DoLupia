// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BossDroneAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API ABossDroneAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABossDroneAIController();
	virtual void OnPossess(APawn* InPawn) override;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

	static const FName& GetAttackTargetKey() { return AttackTargetKey; }
	static const FName& GetStateKey() { return StateKey; }

	virtual void Tick(float DeltaSeconds) override;

protected:
	static const FName AttackTargetKey;
	static const FName StateKey;
	static const FName PointOfInterestKey;
	static const FName AttackRadiusKey;
	static const FName DefendRadiusKey;

private:
	void InitBlackBoardSetting( APawn* InPawn );
	bool CanSenseActor(AActor* OtherActor, uint8 Sense);

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
