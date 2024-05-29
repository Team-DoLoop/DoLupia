// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMonsterAIController::HomePosKey( TEXT( "HomePos" ) );
const FName AMonsterAIController::PatrolPosKey( TEXT( "PatrolPos" ) );
const FName AMonsterAIController::TargetKey( TEXT( "Target" ) );
const FName AMonsterAIController::IsAliveKey( TEXT( "IsAlive" ) );
const FName AMonsterAIController::IsInAttackRangeKey( TEXT( "IsInAttackRange" ) );

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject
	( TEXT( "/Game/Monsters/BossMonster/Blueprints/BB_BossMonster.BB_BossMonster" ) );
	if (BBObject.Succeeded())
		BBAsset = BBObject.Object;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject
	( TEXT( "/Game/Monsters/BossMonster/Blueprints/BT_BossMonster.BT_BossMonster" ) );
	if (BTObject.Succeeded())
		BTAsset = BTObject.Object;
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComponent = Blackboard;

	if(UseBlackboard(BBAsset, BlackboardComponent ))
	{
		Blackboard->SetValueAsVector( HomePosKey , GetPawn()->GetActorLocation() );

		if(!RunBehaviorTree(BTAsset))
		{
			UE_LOG( LogTemp , Warning , TEXT( "AI couldn't run BT" ) );
		}
	}
}



