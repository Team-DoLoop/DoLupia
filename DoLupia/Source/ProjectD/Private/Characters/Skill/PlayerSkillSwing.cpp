// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillSwing.h"

void UPlayerSkillSwing::Execute()
{
	Super::Execute();

	UE_LOG(LogTemp, Log, TEXT("Swing"));
}

void UPlayerSkillSwing::ApplySkill(ACharacter* Target)
{
	Super::ApplySkill(Target);
}
