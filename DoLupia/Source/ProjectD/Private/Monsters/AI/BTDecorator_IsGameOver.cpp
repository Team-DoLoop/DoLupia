// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTDecorator_IsGameOver.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsGameOver::UBTDecorator_IsGameOver()
{
	NodeName = TEXT( "IsGameOver" );

}

bool UBTDecorator_IsGameOver::CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) const
{
	bool bResult = Super::CalculateRawConditionValue( OwnerComp , NodeMemory );

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	bool IsGameOver = OwnerComp.GetBlackboardComponent()->GetValueAsBool( AMonsterAIController::IsGameOverKey );

	if (IsGameOver) {
		bResult = true;
	}

	else {
		bResult = false;
	}
	return bResult;
}
