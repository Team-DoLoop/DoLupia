// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "Animation/AnimInstance.h"
#include "MonsterFSM.h"
#include "RangedMonster.h"
#include "StrikeMonster.h"
#include "MonsterAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UMonsterAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EMonsterState animState;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EMonsterType MonsterType;

	virtual void NativeInitializeAnimation() override;

	UPROPERTY()
	class AStrikeMonster* StrikeMonster;

	UPROPERTY()
	class ARangedMonster* RangedMonster;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	bool bAttackDelay = false;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	bool bIsAttackComplete = false;

	UFUNCTION(BlueprintCallable)
	void OnDoHitAttackAnimation();

	UFUNCTION(BlueprintCallable)
	void OnEndHitAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnDoStrikeDieAnimation();

	UFUNCTION( BlueprintCallable )
	void OnEndRangedAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnDoRangedAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnDoRangedDieAnimation();

	
};
