// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/AI/Tasks/BTT_DefaultAttack.h"

#include "AIController.h"
#include "Monsters/Drone/BossDrone.h"

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ABossDrone* Drone = Cast<ABossDrone>( OwnerComp.GetAIOwner()->GetPawn() ))
	{
		Drone->Attack();
	}
	else
		return EBTNodeResult::Type::Failed;

	return EBTNodeResult::Type::Succeeded;
}
