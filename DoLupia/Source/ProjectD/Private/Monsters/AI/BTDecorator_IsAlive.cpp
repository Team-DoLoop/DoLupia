// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTDecorator_IsAlive.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsAlive::UBTDecorator_IsAlive()
{
	NodeName = TEXT( "IsAlive" );
}

bool UBTDecorator_IsAlive::CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) const
{
	bool bResult = Super::CalculateRawConditionValue( OwnerComp , NodeMemory );

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	auto Boss = Cast<ABossMonster>( OwnerComp.GetAIOwner()->GetPawn() );

	if (Boss->IsAlive) {
		bResult = true;
	}

	else {
		bResult= false;
	}

	return bResult;
}
