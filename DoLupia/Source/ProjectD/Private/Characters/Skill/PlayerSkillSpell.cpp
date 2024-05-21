// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillSpell.h"



UPlayerSkillSpell::UPlayerSkillSpell()
{
	SkillName = "Spell";
	SkillLevel = 1;
	SkillCost = 10;
	SkillCoolTime = 10;
	SkillDamage = 3;
}

void UPlayerSkillSpell::ExecuteSkill()
{
	Super::ExecuteSkill();
	
	UE_LOG(LogTemp, Log, TEXT("Spell"));
}

void UPlayerSkillSpell::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
