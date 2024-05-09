// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAnim.h"
#include "Monsters/Monster.h"

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
