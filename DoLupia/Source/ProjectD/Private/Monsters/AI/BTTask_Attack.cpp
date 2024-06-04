// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTTask_Attack.h"

#include "Monsters/BossAnim.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

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

	//Boss->state = EBossState::Attack;
	//Boss->currentTime = Boss->attackDelayTime;
	IsAttacking = true;

	Boss->anim->OnEndHitAttack.AddLambda( [this]()->void
	{
		IsAttacking = false;
		UE_LOG( LogTemp , Warning , TEXT( "Boss->anim->OnEndHitAttack.AddLambda" ) );

	} );
	Boss->anim->OnEndFireAttack.AddLambda( [this]()->void
	{
		IsAttacking = false;
		UE_LOG( LogTemp , Warning , TEXT( "Boss->anim->OnEndFireAttack.AddLambda" ) );

	} );
	Boss->anim->OnEndGrabAttack.AddLambda( [this]()->void
	{
		IsAttacking = false;
		UE_LOG( LogTemp , Warning , TEXT( "Boss->anim->OnEndGrabAttack.AddLambda" ) );

	} );

	return EBTNodeResult::InProgress;

}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp , NodeMemory , DeltaSeconds);

	if(!IsAttacking)
	{
		FinishLatentTask( OwnerComp , EBTNodeResult::Succeeded );
		UE_LOG( LogTemp , Warning , TEXT( "FinishLatentTask( OwnerComp , EBTNodeResult::Succeeded );" ) );
		IsAttacking = true;

	}
	
}

