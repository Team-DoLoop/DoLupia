// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillFlamethrower.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerSkillFlamethrower : public APlayerSkillBase
{
	GENERATED_BODY()
	
public:
	APlayerSkillFlamethrower();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystem* FireEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFireLength; // 최대 사거리

	void StartFiring();
	void StopFiring();

	void ApplyDamage();
	FVector GetMouseDirection();

private:
	UPROPERTY()
	class UParticleSystemComponent* FireEffectComponent;

	FTimerHandle DamageTimerHandle;

	float Damage;
	float CurrentFireLength;
	float FireSpeed;
};
