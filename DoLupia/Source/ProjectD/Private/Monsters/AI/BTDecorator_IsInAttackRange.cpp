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
	bool bResult = Super::CalculateRawConditionValue( OwnerComp , NodeMemory );

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(nullptr==ControllingPawn)
		return false;

	auto Target = Cast<AProjectDCharacter>( OwnerComp.GetBlackboardComponent()->GetValueAsObject( AMonsterAIController::TargetKey ) );
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo( ControllingPawn ) < 200.0f);
	return bResult;
	//return Super::CalculateRawConditionValue(OwnerComp , NodeMemory);
}
