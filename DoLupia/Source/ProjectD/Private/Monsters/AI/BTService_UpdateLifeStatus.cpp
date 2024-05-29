// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTService_UpdateLifeStatus.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateLifeStatus::UBTService_UpdateLifeStatus()
{
	NodeName = TEXT( "UpdateLifeStatus" );
	Interval = 1.0f;
}

void UBTService_UpdateLifeStatus::TickNode( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds )
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	auto Boss = Cast<ABossMonster>( OwnerComp.GetAIOwner()->GetPawn() );

	OwnerComp.GetBlackboardComponent()->SetValueAsBool( AMonsterAIController::IsAliveKey , Boss->IsAlive );
}
