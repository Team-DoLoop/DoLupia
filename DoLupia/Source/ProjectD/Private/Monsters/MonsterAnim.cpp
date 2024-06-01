// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAnim.h"

#include "Components/CapsuleComponent.h"
#include "Monsters/Monster.h"
#include "Monsters/RangedMonster.h"
#include "Monsters/StrikeMonster.h"

void UMonsterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AMonster>( ownerPawn );


	if(monster)
	{
		//animState= monster->MonsterFSM->state;
	}

}

void UMonsterAnim::OnDoHitAttackAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AStrikeMonster>( ownerPawn );
	monster->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	monster->GetCapsuleComponent()->SetCollisionResponseToChannel( ECC_GameTraceChannel2 , ECR_Overlap );

}

void UMonsterAnim::OnEndHitAttackAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AStrikeMonster>( ownerPawn );

	bAttackDelay = false;
	bIsAttackComplete = true;
}

void UMonsterAnim::SetCollision()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AStrikeMonster>( ownerPawn );
	monster->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	monster->GetCapsuleComponent()->SetCollisionResponseToChannel( ECC_GameTraceChannel2 , ECR_Ignore );
}

void UMonsterAnim::OnDoStrikeDieAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<AStrikeMonster>( ownerPawn );
	monster->DestroyMonster();
}

void UMonsterAnim::OnEndRangedAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
}

void UMonsterAnim::OnDoRangedAttackAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<ARangedMonster>( ownerPawn );
	monster->RangedAttack();
}

void UMonsterAnim::OnDoRangedDieAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	auto monster = Cast<ARangedMonster>( ownerPawn );
	monster->DestroyMonster();
}
