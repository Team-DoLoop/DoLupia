// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAnim.h"
#include "Monsters/Monster.h"
#include "Monsters/RangedMonster.h"

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AMonster>( ownerPawn );


	if(monster)
	{
		animState= monster->MonsterFSM->state;
	}

}

void UMonsterAnim::OnEndHitAttackAnimation()
{
	bAttackDelay = false;
}

void UMonsterAnim::OnEndRangedAttackAnimation()
{
	bAttackDelay = false;
}

void UMonsterAnim::OnDoRangedAttackAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<ARangedMonster>( ownerPawn );
	monster->HasObstacle();
}
