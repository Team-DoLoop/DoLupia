// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAnim.h"

#include "Components/CapsuleComponent.h"
#include "Monsters/Monster.h"
#include "Monsters/RangedMonster.h"
#include "Monsters/StrikeMonster.h"


void UMonsterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	auto ownerPawn = TryGetPawnOwner();
	StrikeMonster = Cast<AStrikeMonster>( ownerPawn );
	RangedMonster = Cast<ARangedMonster>( ownerPawn );
}

void UMonsterAnim::OnDoHitAttackAnimation()
{
	StrikeMonster->IsCollisionEnabled = true;
}

void UMonsterAnim::OnEndHitAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	StrikeMonster->IsCollisionEnabled = false;

}

void UMonsterAnim::OnDoStrikeDieAnimation()
{
	StrikeMonster->DestroyMonster();
}

void UMonsterAnim::OnEndRangedAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
}

void UMonsterAnim::OnDoRangedAttackAnimation()
{
	RangedMonster->RangedAttack();
}

void UMonsterAnim::OnDoRangedDieAnimation()
{
	RangedMonster->DestroyMonster();
}
