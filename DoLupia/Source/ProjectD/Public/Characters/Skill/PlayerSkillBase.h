// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Interfaces/SkillInterface.h"
#include "PlayerSkillBase.generated.h"

/**
 * 
 */

struct FPlayerSkillData;
enum class ESkillType : uint8;
enum class EUseColor : uint8;
UCLASS()
class PROJECTD_API UPlayerSkillBase : public UObject, public ISkillInterface
{
	GENERATED_BODY()
	

protected:

public:
	UPlayerSkillBase();
	
	virtual void ExecuteSkill() override;
	virtual void ApplySkill(ACharacter* Target) override;
	virtual void ChangeSkillData(FPlayerSkillData* _PlayerSkillData);

	/*
	FORCEINLINE virtual FString GetSkillName() const {return SkillName;}
	FORCEINLINE virtual int32 GetSkillLevel() const {return SkillLevel;}
	FORCEINLINE virtual int32 GetSkillCost() const {return SkillCost;}
	FORCEINLINE virtual int32 GetSkillCoolTime() const {return SkillCoolTime;}
	FORCEINLINE virtual int32 GetSkillDamage() const {return SkillDamage;}

	FORCEINLINE virtual void SetSkillName(FString _SkillName) {SkillName = _SkillName;}
	FORCEINLINE virtual void SetSkillLevel(int32 _SkillLevel) {SkillLevel = _SkillLevel;}
	FORCEINLINE virtual void SetSkillCost(int32 _SkillCost) {SkillCost = _SkillCost;}
	FORCEINLINE virtual void SetSkillCoolTime(int32 _SkillCoolTime) {SkillCoolTime = _SkillCoolTime;}
	FORCEINLINE virtual void SetSkillDamage(int32 _SkillDamage) {SkillDamage = _SkillDamage;}
	*/

	
};
