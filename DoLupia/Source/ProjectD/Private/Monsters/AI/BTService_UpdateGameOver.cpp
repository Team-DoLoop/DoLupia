// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTService_UpdateGameOver.h"
#include "Monsters/MonsterAIController.h"
#include "Monsters/BossMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/PlayerStat.h"

UBTService_UpdateGameOver::UBTService_UpdateGameOver()
{
	NodeName = TEXT( "UpdateGameOver" );
	Interval = 1.0f;
}

void UBTService_UpdateGameOver::TickNode( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds )
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;
	
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (player) {
		APlayerStat* PlayerStat = Cast<APlayerStat>( player->GetPlayerState() );

		if (PlayerStat) {
			int PlayerHP = PlayerStat->GetHP();

			if (PlayerHP <= 0) {
				IsGameOver = true;
			}
		}
	}

	
	OwnerComp.GetBlackboardComponent()->SetValueAsBool( AMonsterAIController::IsGameOverKey , IsGameOver );

}
