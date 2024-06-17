// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/LevelManager.h"

#include "Library/GameSaveManager.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"

ALevelManager* ALevelManager::Instance = nullptr;

// Sets default values
ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameSaveManager();
}

void ALevelManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Instance)
	{
		Instance->RemoveFromRoot(); // GC 해제
		Instance->Destroy();
		Instance = nullptr;
	}
}

ALevelManager* ALevelManager::GetInstance( UWorld* World )
{
	if(!Instance)
	{
		Instance = World->SpawnActor<ALevelManager>(StaticClass());
	}

	return Instance;
}

void ALevelManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName, FName SaveName,
	FName LevelName , FVector Location, TArray<UItemBase*> ItemBases, bool UseThread, bool UseLocation )
{
	if(GameSaveManager)
	{
		GameSaveManager->SaveGame( Character, SaveType, SaveSlotName, SaveName, LevelName, Location, ItemBases, UseLocation );
	}
}

void ALevelManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName, FName SaveName,
	FName LevelName, FVector Location, TArray<UItemBase*> ItemBases, bool UseLocation, 
	FString QuickSlot1, FString QuickSlot2, FString QuickSlot3, FString QuickSlot4)
{
	if (GameSaveManager)
	{
		GameSaveManager->SaveGame( Character , SaveType , SaveSlotName , SaveName , LevelName , Location , ItemBases , UseLocation, QuickSlot1, QuickSlot2, QuickSlot3, QuickSlot4 );
	}
}

void ALevelManager::LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName, bool UseLocation, bool UseThread, bool OpenLevel )
{
	if (GameSaveManager)
	{
		GameSaveManager->LoadGame( Character, SaveType , SaveSlotName, UseLocation, UseThread, OpenLevel );
	}
}



void ALevelManager::InitializeGameSaveManager()
{
	GameSaveManager = GetWorld()->SpawnActor<AGameSaveManager>( AGameSaveManager::StaticClass() );
}

