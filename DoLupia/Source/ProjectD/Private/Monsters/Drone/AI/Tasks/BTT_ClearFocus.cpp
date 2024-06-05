// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/AI/Tasks/BTT_ClearFocus.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/Drone/AI/BossDroneAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Tasks/AITask_MoveTo.h"

using namespace EBTNodeResult;

UBTT_ClearFocus::UBTT_ClearFocus()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
	NodeName = "ClearFocus";
}

EBTNodeResult::Type UBTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (!BlackboardComponent)
		return Failed;

	FVector Point = BlackboardComponent->GetValueAsVector( ABossDroneAIController::GetPointOfInterestKey() );
	//Point.Z += 200.f;
	//BlackboardComponent->SetValueAsVector( ABossDroneAIController::GetPointOfInterestKey(), Point );
	
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return Failed;

	APawn* Owner = AIController->GetPawn();

	if(!Owner)
		return Failed;

	return InProgress;
}

void UBTT_ClearFocus::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp , NodeMemory , DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();


	if (!BlackboardComponent)
		return;

	FVector Point = BlackboardComponent->GetValueAsVector( ABossDroneAIController::GetPointOfInterestKey() );
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController)
		return;

	APawn* Owner = AIController->GetPawn();
	Owner->SetActorLocation( FMath::Lerp( Owner->GetActorLocation() , Point , 0.03f ) );

	if ((Point - Owner->GetActorLocation()).Length() < 50.f)
	{
		FinishLatentTask( OwnerComp , Succeeded );
	}
}
