// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/AI/Decorators/BTD_CanSeeTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monsters/Drone/AI/BossDroneAIController.h"

UBTD_CanSeeTarget::UBTD_CanSeeTarget()
{
	NodeName = "CanSeeTarget";
}

bool UBTD_CanSeeTarget::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(!BlackboardComponent)
		return false;

	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject( ABossDroneAIController::GetAttackTargetKey() ));

	if(!Target)
		return false;

	AAIController* AIController = OwnerComp.GetAIOwner();

	if(!AIController)
		return false;

	APawn* ControlledPawn = AIController->GetPawn();

	if (!ControlledPawn)
		return false;

	TArray<FHitResult> OutHits;
	
	TArray<AActor*> IgnoreToActors;
	IgnoreToActors.Add(ControlledPawn);

	if(bool bHit = UKismetSystemLibrary::LineTraceMulti
	(
		ControlledPawn,
		ControlledPawn->GetActorLocation(),
		Target->GetActorLocation(),
		TraceTypeQuery1,
		false,
		IgnoreToActors,
		EDrawDebugTrace::ForDuration,
		OutHits,
		true
	))
	{
		for(auto& Hit : OutHits)
		{
			if(Hit.GetActor()->IsA( AProjectDCharacter::StaticClass() ))
			{
				return true;	
			}

			UE_LOG(LogTemp, Log, TEXT("Hit : %s"), *Hit.GetActor()->GetName());
		}
	}

	return false;
}
