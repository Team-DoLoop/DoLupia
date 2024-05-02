// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString JsonParse( const FString& data );
	static FString MapToJson( const TMap<FString, FString>& map);
	static bool SaveJson( const FString& filename, const FString& json );
	
};
