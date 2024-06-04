// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/AI/BossDroneAIController.h"

#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/Drone/BossDrone.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

const FName ABossDroneAIController::AttackTargetKey( TEXT( "AttackTarget" ) );
const FName ABossDroneAIController::StateKey( TEXT( "State" ) );
const FName ABossDroneAIController::PointOfInterestKey( TEXT( "PointOfInterest" ) );
const FName ABossDroneAIController::AttackRadiusKey( TEXT( "AttackRadius" ) );
const FName ABossDroneAIController::DefendRadiusKey( TEXT( "DefendRadius" ) );

ABossDroneAIController::ABossDroneAIController()
{

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject( TEXT( "BlackboardData'/Game/Monsters/BossMonster/Blueprints/Drone/AI/BehaviorTree/BB_BossDroneBase.BB_BossDroneBase'" ) );
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject( TEXT( "BehaviorTree'/Game/Monsters/BossMonster/Blueprints/Drone/AI/BehaviorTree/BT_DroneBase.BT_DroneBase'" ) );
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void ABossDroneAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess( InPawn );

	InitBlackBoardSetting(InPawn);
	

	UBlackboardComponent* BlackboardComponent = Blackboard;
	if (UseBlackboard( BBAsset , BlackboardComponent ))
	{
		RunBehaviorTree( BTAsset );

	}
}

void ABossDroneAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	Super::ActorsPerceptionUpdated(UpdatedActors);

	for(auto& ArrayElement : UpdatedActors)
	{
		
	}

}

void ABossDroneAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if( Blackboard->GetValueAsEnum( StateKey ) != static_cast<uint8>(EDroneState::Attacking))
	{
		Blackboard->SetValueAsObject( AttackTargetKey , GetWorld()->GetFirstPlayerController()->GetPawn() );
		Blackboard->SetValueAsEnum( StateKey , static_cast<uint8>(EDroneState::Attacking) );
	}
}

void ABossDroneAIController::InitBlackBoardSetting( APawn* InPawn )
{
	ABossDrone* Drone = Cast<ABossDrone>( InPawn );

	if (Drone)
	{
		RunBehaviorTree( BTAsset );
		Blackboard->SetValueAsEnum( StateKey , static_cast<uint8>(EDroneState::Following) );
		Blackboard->SetValueAsFloat( AttackRadiusKey , Drone->GetAttackRange() );
		Blackboard->SetValueAsFloat( DefendRadiusKey , Drone->GetFollowRange() );
		//BBAsset
	}
}

bool ABossDroneAIController::CanSenseActor(AActor* OtherActor, uint8 Sense)
{
	FActorPerceptionBlueprintInfo Info;
	UAIPerceptionComponent* AIPerception = GetAIPerceptionComponent();

	if(AIPerception->GetActorsPerception(OtherActor, Info))
	{
		for (auto& ArrayElement : Info.LastSensedStimuli)
		{
			if(TSubclassOf<UAISense> SensedClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, ArrayElement))
			{
				if(ArrayElement.SensingSucceeded)
					return true;
			}
		}
	}

	return false;
}
