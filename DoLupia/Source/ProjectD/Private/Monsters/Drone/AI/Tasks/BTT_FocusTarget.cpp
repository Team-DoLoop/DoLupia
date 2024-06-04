// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/AI/Tasks/BTT_FocusTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/Drone/AI/BossDroneAIController.h"

using namespace EBTNodeResult;

Type UBTT_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(!BlackboardComponent)
		return Failed;

	AActor* Character = Cast<AActor>(BlackboardComponent->GetValueAsObject(ABossDroneAIController::GetAttackTargetKey()));
	AAIController* AIController = OwnerComp.GetAIOwner();

	if(!Character || !AIController)
		return Failed;

	AIController->SetFocus(Character);

	FinishLatentTask(OwnerComp, Succeeded);

	return Succeeded;
}
