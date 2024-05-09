// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillCastingHitDown.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillCastingHitDown : public UPlayerSkillBase
{
	GENERATED_BODY()

		
private:
		

protected:

public:
	virtual void Execute() override;
	virtual void ApplySkill(class ACharacter* Target) override;
};
