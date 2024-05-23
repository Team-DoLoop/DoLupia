// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerStatusEffectComp.h"

UPlayerStatusEffectComp::UPlayerStatusEffectComp()
{
	
}

void UPlayerStatusEffectComp::SetStatusEffect(EEffectAttackType _statusEffect)
{
	Super::SetStatusEffect(_statusEffect);

	
}

void UPlayerStatusEffectComp::AddStatusEffect(ACharacter* Target)
{
	Super::AddStatusEffect(Target);
}
