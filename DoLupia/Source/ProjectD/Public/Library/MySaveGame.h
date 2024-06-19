﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

enum class EUseColor : uint8;
enum class EItemType : uint8;
class UItemBase;

USTRUCT()
struct FSaveGameDefault
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	TMap<FString , int32> ItemBases;

	// 저장된 위치
	UPROPERTY()
	FVector Location;

	UPROPERTY()
	bool IsUseLocation;

	// 저장된 위치
	UPROPERTY()
	FRotator Rotation;

	// 세이브 이름
	UPROPERTY()
	FName SaveName;

	// 장착된 아이템
	UPROPERTY()
	TMap<EItemType , FString> EquippedItems;

	UPROPERTY()
	FName LevelName;

	// 망토
	UPROPERTY()
	FName PlayerCape;


	// 퀵 슬롯 데이터
	UPROPERTY()
	FString QuickSlotKey1;

	UPROPERTY()
	FString QuickSlotKey2;

	UPROPERTY()
	FString QuickSlotKey3;

	UPROPERTY()
	FString QuickSlotKey4;

	UPROPERTY()
	int32 QuickSlotValue1;

	UPROPERTY()
	int32 QuickSlotValue2;

	UPROPERTY()
	int32 QuickSlotValue3;

	UPROPERTY()
	int32 QuickSlotValue4;
	
	// 튜토리얼
	UPROPERTY()
	TMap<int32, bool> ToToAutoSaveData;

	UPROPERTY()
	TMap<EUseColor , bool> CanUseColor;

	UPROPERTY()
	TArray<int32> PlayerSkillLevel;
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
