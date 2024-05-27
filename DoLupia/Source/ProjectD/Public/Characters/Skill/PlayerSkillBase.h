// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/SkillInterface.h"
#include "UObject/NoExportTypes.h"
#include "PlayerSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillBase : public UObject, public ISkillInterface
{
	GENERATED_BODY()
	
private:

protected:

public:
	UPlayerSkillBase();

	virtual void SetSkillUI();
	virtual void ExecuteSkill() override;
	virtual void ApplySkill(ACharacter* Target) override;
};
