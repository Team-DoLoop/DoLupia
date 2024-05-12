// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "Animation/AnimInstance.h"
#include "MonsterFSM.h"
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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	bool bAttackDelay = false;

	UFUNCTION(BlueprintCallable)
	void OnEndHitAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnEndRangedAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnDoRangedAttackAnimation();
};
