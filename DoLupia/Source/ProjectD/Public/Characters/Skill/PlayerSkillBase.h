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
	FString SkillName;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillLevel;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCost;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillCoolTime;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	int32 SkillDamage;

public:
	UPlayerSkillBase();

	FORCEINLINE virtual FString GetSkillName() const {return SkillName;}
	FORCEINLINE virtual int32 GetSkillLevel() const {return SkillLevel;}
	FORCEINLINE virtual int32 GetSkillCost() const {return SkillCost;}
	FORCEINLINE virtual int32 GetSkillCoolTime() const {return SkillCoolTime;}
	FORCEINLINE virtual int32 GetSkillDamage() const {return SkillDamage;}

	virtual void ExecuteSkill() override;
	virtual void ApplySkill(ACharacter* Target) override;
};
