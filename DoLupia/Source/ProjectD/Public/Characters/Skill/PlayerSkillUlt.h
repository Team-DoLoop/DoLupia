// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillUlt.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerSkillUlt : public APlayerSkillBase
{
	GENERATED_BODY()

public:
	APlayerSkillUlt();

	virtual void BeginPlay() override;

protected:
	virtual void ActivateSkill() override;

public:
	// FORCEINLINE void SetDamage(int32 _Damage){Damage = _Damage;}
	// virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void ApplyDamage(float SkillRadius, int32 _Damage);

private:
	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 CenterDamage = 500;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 MidDamage = 200;

	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 OuterDamage = 100;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float CenterRadius = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float MidRadius = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float OuterRadius = 400.0f;
	
	// int32 Damage = 0;
	
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComp;

	//UPROPERTY(EditAnywhere)
	//class UBoxComponent* BoxComp;
};
