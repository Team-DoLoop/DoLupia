// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillSpell.h"


void UPlayerSkillSpell::Execute()
{
	Super::Execute();
	
	UE_LOG(LogTemp, Log, TEXT("Spell"));
}

void UPlayerSkillSpell::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
