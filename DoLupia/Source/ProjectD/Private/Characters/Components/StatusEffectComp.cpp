// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/StatusEffectComp.h"

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

void UStatusEffectComp::SetStatusEffect(EStatusEffect _statusEffect)
{
	switch (_statusEffect)
	{
	case EStatusEffect::BLEED : SetBleedEffect(); break;
	case EStatusEffect::POISON : SetPoisonEffect(); break;
	}

	ApplyStatusEffect();
}

void UStatusEffectComp::SetBleedEffect()
{
	IsDotAttack = true;
}

void UStatusEffectComp::SetPoisonEffect()
{
	
}

void UStatusEffectComp::ApplyStatusEffect()
{
	
}

