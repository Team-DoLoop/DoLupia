// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillSwap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillSwap : public UPlayerSkillBase
{
	GENERATED_BODY()

public:

private:
	virtual void ExecuteSkill() override;
};
