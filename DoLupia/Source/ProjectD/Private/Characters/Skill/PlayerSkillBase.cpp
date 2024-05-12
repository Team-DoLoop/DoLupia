// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillBase.h"

#include "Characters/PlayerStateBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerFSMComp.h"


UPlayerSkillBase::UPlayerSkillBase()
	: SkillName(""),
	  SkillLevel(0),
	  SkillCost(0),
	  SkillCoolTime(0),
	  SkillDamage(0)
{
}

void UPlayerSkillBase::Execute()
{
}

void UPlayerSkillBase::ApplySkill(ACharacter* Target)
{
}
