// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BezierMovementLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UBezierMovementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void MoveObjectAlongCurve( UObject* WorldContextObject , AActor* Item , FVector StartPoint, 
		FVector ActorSpeed, float GravityScale, float Time );

	static FVector VectorSeed( AActor* ContextActor);

private:
	static void UpdateObjectPosition( UObject* WorldContextObject , AActor* Item , FVector StartPoint, 
		FVector ActorSpeed, float GravityScale, float Time );
};
