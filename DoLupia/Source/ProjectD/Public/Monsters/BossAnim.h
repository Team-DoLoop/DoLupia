// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossMonster.h"
#include "Animation/AnimInstance.h"
#include "BossAnim.generated.h"

DECLARE_MULTICAST_DELEGATE( FEndHitAttackDelegate );
DECLARE_MULTICAST_DELEGATE( FEndFireAttackDelegate );
DECLARE_MULTICAST_DELEGATE( FEndGrabAttackDelegate );

UCLASS()
class PROJECTD_API UBossAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossState animState;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossSkill animBossSkill;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAttackState = false;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	bool bAttackDelay = false;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite )
	bool bIsAttackComplete = true;

	FEndHitAttackDelegate OnEndHitAttack;
	FEndFireAttackDelegate OnEndFireAttack;
	FEndGrabAttackDelegate OnEndGrabAttack;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

	UFUNCTION( BlueprintCallable )
	void OnEndHitAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnEndFireAttackAnimation();

	UFUNCTION( BlueprintCallable )
	void OnEndGrabAttackAnimation();
};
