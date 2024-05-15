// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillSpell.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillSpell : public UPlayerSkillBase
{
	GENERATED_BODY()
private:

	
public:
	UPlayerSkillSpell();
	
	virtual void ExecuteSkill() override;
	virtual void ApplySkill(class ACharacter* Target) override;
};
