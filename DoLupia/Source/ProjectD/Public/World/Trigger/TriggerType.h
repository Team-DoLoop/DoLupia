// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TriggerType.generated.h"


UENUM( BlueprintType )
enum class EPlayerTriggerType : uint8
{
	None			UMETA( DisplayName = "None" ) ,
	LevelTransition UMETA( DisplayName = "Level Transition" ) ,
	CameraAngle     UMETA( DisplayName = "Camera Angle" ),
	CameraTargetArms     UMETA( DisplayName = "Camera Boom Length" )
};


/**
 * 
 */
UCLASS()
class PROJECTD_API UTriggerType : public UObject
{
	GENERATED_BODY()
	
};
