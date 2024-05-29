// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTDecorator_IsInAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/MonsterAIController.h"
#include "Characters/ProjectDCharacter.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT( "CanAttack" );
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue( OwnerComp , NodeMemory );
	bool bResult = false;

	bResult=  OwnerComp.GetBlackboardComponent()->GetValueAsBool( AMonsterAIController::IsInAttackRangeKey  );

	

	return bResult;
}
