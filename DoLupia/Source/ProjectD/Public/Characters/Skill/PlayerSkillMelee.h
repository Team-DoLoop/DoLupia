// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillMelee.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillMelee : public UPlayerSkillBase
{
	GENERATED_BODY()


private:

public:
	virtual void SetSkillUI() override;
	virtual void ExecuteSkill() override;
	
};
