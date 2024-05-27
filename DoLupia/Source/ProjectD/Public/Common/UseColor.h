// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UseColor.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EUseColor : uint8
{
	NONE UMETA(DisplayName = "None"),
	RED UMETA(DisplayName = "Red"),
	YELLOW UMETA(DisplayName = "Yellow"),
	BLUE UMETA(DisplayName = "Blue"),
	COLOR UMETA(DisplayName = "Color"),
};

UCLASS()
class PROJECTD_API UUseColor : public UObject
{
	GENERATED_BODY()
	
};
