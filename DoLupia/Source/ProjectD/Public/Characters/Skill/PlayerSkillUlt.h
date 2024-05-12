// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillUlt.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillUlt : public UPlayerSkillBase
{
	GENERATED_BODY()
	
private:
		

protected:

public:
	UPlayerSkillUlt();
	
	virtual void Execute() override;
	virtual void ApplySkill(class ACharacter* Target) override;
};
