// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillSwing.h"

UPlayerSkillSwing::UPlayerSkillSwing()
{
	SkillName = "Swing";
	SkillLevel = 1;
	SkillCost = 10;
	SkillCoolTime = 5;
	SkillDamage = 10;
}

void UPlayerSkillSwing::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Log, TEXT("Swing"));
}

void UPlayerSkillSwing::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
