// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsGameOver.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UBTDecorator_IsGameOver : public UBTDecorator
{
	GENERATED_BODY()

public:

	UBTDecorator_IsGameOver();
	virtual bool CalculateRawConditionValue( UBehaviorTreeComponent& OwnerComp , uint8* NodeMemory ) const override;

	
};
