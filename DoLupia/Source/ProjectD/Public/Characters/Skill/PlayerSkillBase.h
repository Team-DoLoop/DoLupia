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

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	FString SkillName;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillLevel;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCost;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCoolTime;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillDamage;
	
	virtual void Execute() override;
	virtual void ApplySkill(ACharacter* Target) override;
};
