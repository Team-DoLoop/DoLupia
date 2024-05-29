// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateLifeStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UBTService_UpdateLifeStatus : public UBTService
{
	GENERATED_BODY()
	
public:
	//보스 생사 업데이트
	UBTService_UpdateLifeStatus();

	virtual void TickNode( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory , float DeltaSeconds ) override;

	
};
