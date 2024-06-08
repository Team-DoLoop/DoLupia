﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

class UItemBase;
enum class EItemType : uint8;

USTRUCT()
struct FSaveGameDefault
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FString , int32> ItemBases;

	// 저장된 위치
	UPROPERTY()
	FVector Location;

	// 세이브 이름
	UPROPERTY()
	FName SaveName;

	// 장착된 아이템
	UPROPERTY()
	TMap<EItemType , FString> EquippedItems;

	// 망토
	UPROPERTY()
	FName PlayerCape;
};



/**
 * 
 */
UCLASS()
class PROJECTD_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()


public:
	UPROPERTY()
	FString SaveSlotName;		// Save game data file name

	UPROPERTY()
	int32 SaveIndex;		

	UPROPERTY()
	TMap<FString , int32> ItemBases;

	// 저장된 위치
	UPROPERTY()
	FVector Location;

	// 세이브 이름
	UPROPERTY()
	FName SaveName;

	// 장착된 아이템
	UPROPERTY()
	TMap<EItemType , FString> EquippedItems;

	// 망토
	UPROPERTY()
	FName PlayerCape;

	UPROPERTY()
	FSaveGameDefault SaveStruct;

};
