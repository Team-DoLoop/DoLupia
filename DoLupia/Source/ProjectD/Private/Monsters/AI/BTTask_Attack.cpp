// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTTask_Attack.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true; // 매 프레임마다 TickTask 호출
	IsAttacking = false; //현재 공격 중인지
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask( OwnerComp , NodeMemory );

	auto Boss = Cast<ABossMonster>( OwnerComp.GetAIOwner()->GetPawn() );
	if (nullptr == Boss)
		return EBTNodeResult::Failed;


	Boss->state = EBossState::Attack;
	
	//IsAttacking = true;

	/*if (!IsAttacking)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UBTTask_Attack::공격 끝" ) );

		return EBTNodeResult::Succeeded;
	}*/
	return EBTNodeResult::Succeeded;

	
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp , NodeMemory , DeltaSeconds);

	
}

void UBTTask_Attack::OnAttackEndHandle()
{
	IsAttacking = false;
}

