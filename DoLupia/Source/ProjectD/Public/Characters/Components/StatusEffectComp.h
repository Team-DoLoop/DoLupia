// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComp.generated.h"

//class USoundBase;
//class UParticleSystem;

UENUM(BlueprintType)
enum class EStatusEffect : uint8
{
	BLEED UMETA(DisplayName = "Bleed"),
	POISON UMETA(DisplayName = "Poison")
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UStatusEffectComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;





private:
	//UPROPERTY(EditAnywhere)
	//USoundBase* SFX;

	//UPROPERTY(EditAnywhere)
	// UParticleSystem* VFX;

	float TakeDamage = 0.0f;

	bool IsDotAttack = false;

	//TMap<EStatusEffect, USoundBase> StatusEffectSFX;
	//TMap<EStatusEffect, UParticleSystem> StatusEffectVFX;

protected:

public:
	void SetStatusEffect(EStatusEffect _statusEffect);
	void SetBleedEffect();
	void SetPoisonEffect();
	
	void ApplyStatusEffect();
};
