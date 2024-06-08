// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

class AGameSaveManager;
class AProjectDCharacter;
class UItemBase;
enum class ESaveType;

UCLASS()
class PROJECTD_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	static ALevelManager* GetInstance(UWorld* World);

	// 저장 및 로드 함수
	void SaveGame( AProjectDCharacter* Character, ESaveType SaveType , FString SaveSlotName , FName SaveName , FVector Location , TArray<UItemBase*> ItemBases, bool UseThread );
	void LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName , FName SaveName , FVector Location , TArray<UItemBase*> ItemBases, bool UseThread );

private:
	void InitializeGameSaveManager();

private:
	// 싱글톤 인스턴스
	static ALevelManager* Instance;

	UPROPERTY()
	AGameSaveManager* GameSaveManager;
};
