// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillElecBlast.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerSkillElecBlast : public APlayerSkillBase
{
	GENERATED_BODY()
	
public:
	APlayerSkillElecBlast();

	virtual void BeginPlay() override;

	virtual void ActivateSkill() override;

	FORCEINLINE void SetSkillDamage(int32 _SkillDamage){SkillDamage = _SkillDamage;}

private:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComp;

	int32 SkillDamage;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	float SkillRadius = 300.0f;
	
};
