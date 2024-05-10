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
	UPROPERTY(VisibleAnywhere, Category = "Skill")
	FString SkillName = "";

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillLevel = 0;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCost = 0;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCoolTime = 0;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillDamage = 0;

public:
	virtual void Execute() override;
	virtual void ApplySkill(ACharacter* Target) override;
};
