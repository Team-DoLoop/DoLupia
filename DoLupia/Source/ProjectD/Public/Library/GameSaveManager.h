// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySaveGame.h"
#include "GameFramework/Actor.h"
#include "GameSaveManager.generated.h"

struct FSaveGameDefault;
class AProjectDCharacter;
class UItemPool;

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

	void SaveGame( AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName , FName SaveName, FVector Location , TArray<UItemBase*> ItemBases  );
	void LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName );

	FORCEINLINE void InputSaveData(const FSaveGameDefault& SaveData) { SaveDataArray.Add( SaveData.SaveName, SaveData ); }

protected:
	virtual void BeginPlay() override;

private:
	void SaveGameAsync( AProjectDCharacter* Character, FString SaveSlotName , FName SaveName , int32 SaveIndex , FVector Location , TArray<UItemBase*> ItemBases );
	void LoadGameAsync( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName );

private:
	UPROPERTY()
	TMap<FName, FSaveGameDefault> SaveDataArray;

	UPROPERTY()
	UItemPool* ItemPool;

};
