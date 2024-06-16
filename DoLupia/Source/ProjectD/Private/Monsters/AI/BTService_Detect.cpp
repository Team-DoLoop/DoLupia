// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/AI/BTService_Detect.h"
#include "Monsters/MonsterAIController.h"
#include "Characters/ProjectDCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h" 
#include "Engine/EngineTypes.h"  
#include "Engine/OverlapResult.h"
#include "Monsters/BossMonster.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT( "Detect" );
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp , NodeMemory , DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World) return;

	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 3000.0f;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam( NAME_None , false , ControllingPawn ); 
	bool bResult = GetWorld()->OverlapMultiByChannel(
		OverlapResults ,
		Center , 
		FQuat::Identity ,
		ECollisionChannel::ECC_GameTraceChannel1 ,
		FCollisionShape::MakeSphere( DetectRadius ) , 
		CollisionQueryParam
	);


	auto Boss = Cast<ABossMonster>( OwnerComp.GetAIOwner()->GetPawn() );


	if(bResult)
	{
		for(auto const& OverlapResult : OverlapResults)
		{
			AProjectDCharacter* player = Cast<AProjectDCharacter>( OverlapResult.GetActor() );
			if(player) //&&player->GetController()->IsPlayerController()
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject( AMonsterAIController::TargetKey , player );

				/*DrawDebugSphere( World , Center , DetectRadius , 16 , FColor::Green , false , 0.2f );
				DrawDebugPoint( World , player->GetActorLocation() , 10 , FColor::Blue , false , 0.2f );
				DrawDebugLine( World , ControllingPawn->GetActorLocation() ,player->GetActorLocation(), FColor::Blue , false , 0.2f );*/

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject( AMonsterAIController::TargetKey , nullptr );

	//DrawDebugSphere( World , Center , DetectRadius , 16 , FColor::Red , false , 0.2f );
	
}
