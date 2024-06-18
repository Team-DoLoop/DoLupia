﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySaveGame.h"
#include "GameFramework/Actor.h"
#include "GameSaveManager.generated.h"

struct FSaveGameDefault;
class AProjectDCharacter;
class UItemPool;
class ASaveLoadObject;

UENUM()
enum class ESaveType
{
	SAVE_AUTO,
	SAVE_MAIN,
	SAVE_1,
	SAVE_2,
	SAVE_3,
	SAVE_4,
	SAVE_5,
	SAVE_END
};

UCLASS()
class PROJECTD_API AGameSaveManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGameSaveManager();

	// [[deprecated]]
	void SaveGame( AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName , FName SaveName, FName LevelName,
		FVector Location , TArray<UItemBase*> ItemBases, bool UseLocation );

	void SaveGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName , FName SaveName , FName LevelName ,
		FVector Location , TArray<UItemBase*> ItemBases, bool UseLocation,
		FString QuickSlot1 , FString QuickSlot2 , FString QuickSlot3, FString QuickSlot4);
	
	void LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName, bool UseLocation , bool UseThread , bool OpenLevel );

	FORCEINLINE void InputSaveData(const FSaveGameDefault& SaveData) { SaveDataArray.Add( SaveData.SaveName, SaveData ); }

protected:
	virtual void BeginPlay() override;

private:
	void SaveGameAsync( AProjectDCharacter* Character, FString SaveSlotName , FName SaveName , FName LevelName,
		int32 SaveIndex , FVector Location , TArray<UItemBase*> ItemBases, bool UseLocation );

	void SaveGameAsync( AProjectDCharacter* Character , FString SaveSlotName , FName SaveName , FName LevelName ,
		int32 SaveIndex , FVector Location , TArray<UItemBase*> ItemBases , bool UseLocation ,
		FString QuickSlot1 , FString QuickSlot2 , FString QuickSlot3 , FString QuickSlot4 );

	void LoadGameAsync( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName, bool UseLocation , bool UseThread, bool OpenLevel );

private:
	UPROPERTY()
	TMap<FName, FSaveGameDefault> SaveDataArray;

	UPROPERTY()
	UItemPool* ItemPool;

	UPROPERTY()
	ASaveLoadObject* SaveLoadObject;

};
