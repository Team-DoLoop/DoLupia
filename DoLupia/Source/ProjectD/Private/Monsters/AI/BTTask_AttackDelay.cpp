// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTTask_AttackDelay.h"

UBTTask_AttackDelay::UBTTask_AttackDelay()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_AttackDelay::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp , NodeMemory);
}
