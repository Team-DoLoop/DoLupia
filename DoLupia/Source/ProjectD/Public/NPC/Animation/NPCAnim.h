// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnim.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UNPCAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bTalking;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bDie;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bSitting;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bAttack;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	bool bLeaderTalking;
	
};
