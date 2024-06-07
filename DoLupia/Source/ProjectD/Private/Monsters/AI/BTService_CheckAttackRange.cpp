// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/MonsterAIController.h"
#include "Characters/ProjectDCharacter.h"
#include "Monsters/BossAnim.h"
#include "Monsters/BossMonster.h"

UBTService_CheckAttackRange::UBTService_CheckAttackRange()
{
	NodeName = TEXT( "CheckAttackRange" );
	Interval = 1.0f;
}

void UBTService_CheckAttackRange::TickNode( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds )
{
	Super::TickNode( OwnerComp , NodeMemory , DeltaSeconds );
	
	bool bResult = false;

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return ;

	auto Target = Cast<AProjectDCharacter>( OwnerComp.GetBlackboardComponent()->GetValueAsObject( AMonsterAIController::TargetKey ) );
	if (nullptr == Target)
		return ;

	auto Boss = Cast<ABossMonster>( OwnerComp.GetAIOwner()->GetPawn() );

	bResult = (Target->GetDistanceTo( ControllingPawn ) < 1600.0f);

	if (bResult) {

		OwnerComp.GetBlackboardComponent()->SetValueAsBool( AMonsterAIController::IsInAttackRangeKey , true );
		Boss->state = EBossState::Attack;

		
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool( AMonsterAIController::IsInAttackRangeKey , NULL );
		if(Boss->anim->bIsAttackComplete)
		{
			Boss->state = EBossState::Move;

		}
	}
}
