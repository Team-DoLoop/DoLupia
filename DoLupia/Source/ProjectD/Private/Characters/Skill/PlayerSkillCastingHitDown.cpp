// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillCastingHitDown.h"

UPlayerSkillCastingHitDown::UPlayerSkillCastingHitDown()
{
	SkillName = "CastingHitDown";
	SkillLevel = 1;
	SkillCost = 15;
	SkillCoolTime = 20;
	SkillDamage = 10;
}

void UPlayerSkillCastingHitDown::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Log, TEXT("CastingHitDown"));
}

void UPlayerSkillCastingHitDown::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
