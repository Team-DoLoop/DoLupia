// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/LevelManager.h"

#include "Library/GameSaveManager.h"
#include "Characters/ProjectDCharacter.h"

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

	AProjectDCharacter* MyCharacter = Cast<AProjectDCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	GameSaveManager->LoadGame( MyCharacter , ESaveType::SAVE_MAIN , "PlayerMainSave");
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

void ALevelManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName, 
	FName SaveName, FVector Location, TArray<UItemBase*> ItemBases, bool UseThread )
{
	if(GameSaveManager)
	{
		GameSaveManager->SaveGame( Character, SaveType, SaveSlotName, SaveName, Location, ItemBases);
	}
}

void ALevelManager::LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName , 
	FName SaveName , FVector Location , TArray<UItemBase*> ItemBases, bool UseThread )
{
	if (GameSaveManager)
	{
		GameSaveManager->LoadGame( Character, SaveType , SaveSlotName );
	}
}



void ALevelManager::InitializeGameSaveManager()
{
	GameSaveManager = GetWorld()->SpawnActor<AGameSaveManager>( AGameSaveManager::StaticClass() );
}

