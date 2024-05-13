// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillUlt.h"

UPlayerSkillUlt::UPlayerSkillUlt()
{
}

void UPlayerSkillUlt::ExecuteSkill()
{
	Super::ExecuteSkill();

	UE_LOG(LogTemp, Log, TEXT("Ult"));
}

void UPlayerSkillUlt::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
