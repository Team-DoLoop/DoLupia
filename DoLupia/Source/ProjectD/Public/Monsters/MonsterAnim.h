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
	EMonsterState state;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	EMonsterType MonsterType;
};
