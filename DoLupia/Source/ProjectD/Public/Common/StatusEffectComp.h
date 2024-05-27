// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackType.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComp.generated.h"

//class USoundBase;
//class UParticleSystem;

// -> AttackType으로 이동
/*
UENUM(BlueprintType)
enum class EStatusEffectType : uint8
{
	NONE = 0 UMETA(DisplyaName = "None"),
	BLEED = 1 UMETA(DisplayName = "Bleed"),
	POISON = 2 UMETA(DisplayName = "Poison")
};
*/

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

protected:
	//UPROPERTY(EditAnywhere)
	//USoundBase* SFX;

	//UPROPERTY(EditAnywhere)
	// UParticleSystem* VFX;

	UPROPERTY()
	EEffectAttackType statusEffectType = EEffectAttackType::NONE;
	
public:
	float TakeDamage = 0.0f;
	bool IsDotAttack = false;

	// 대상에게 줄 효과 Set
	virtual void SetStatusEffect(EEffectAttackType _statusEffect);

	// Target에게 상태 이상 효과 적용
	virtual void AddStatusEffect(class ACharacter* Target);

	
	virtual void BleedingStatusEffect();
	virtual void PoisonStatusEffect(); 
};
