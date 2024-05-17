// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/StatusEffectComp.h"

// Sets default values for this component's properties
UStatusEffectComp::UStatusEffectComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusEffectComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusEffectComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusEffectComp::SetStatusEffect(EStatusEffectType _statusEffect)
{
	// 어떤 StatusEffect인지에 따라
	// Damage, IsDotAttack, VFX, SFX 설정
	switch (_statusEffect)
	{
	case EStatusEffectType::NONE : break;
	case EStatusEffectType::BLEED : BleedingStatusEffect(); break;
	case EStatusEffectType::POISON : PoisonStatusEffect(); break;
	}

	// AddStatusEffect();
}

void UStatusEffectComp::AddStatusEffect(ACharacter* Target)
{
	// 설정한 값들 Target에 적용
}

void UStatusEffectComp::BleedingStatusEffect()
{
	statusEffectType = EStatusEffectType::BLEED;
}

void UStatusEffectComp::PoisonStatusEffect()
{
	statusEffectType = EStatusEffectType::POISON;
}


