// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillSpell.h"



UPlayerSkillSpell::UPlayerSkillSpell()
{
	SkillName = "a";
	SkillLevel = 0;
	SkillCost = 0;
	SkillCoolTime = 0;
	SkillDamage = 0;
}

void UPlayerSkillSpell::Execute()
{
	Super::Execute();
	
	UE_LOG(LogTemp, Log, TEXT("Spell"));
}

void UPlayerSkillSpell::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
