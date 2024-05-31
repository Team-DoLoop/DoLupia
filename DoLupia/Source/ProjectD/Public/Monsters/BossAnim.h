// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossMonster.h"
#include "Animation/AnimInstance.h"
#include "BossAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UBossAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EBossState animState;

	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;
};
