// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/LevelManager.h"

#include "ProjectDGameInstance.h"
#include "Library/GameSaveManager.h"
#include "Characters/ProjectDCharacter.h"
#include "Common/UseColor.h"
#include "GameFramework/PlayerStart.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"

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

void ALevelManager::LoadChpater(int32 LevelIndex)
{
	AProjectDCharacter* Character = Cast<AProjectDCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if(LevelIndex == 1)
		LoadChapter1();
		
	if (LevelIndex == 2)
		LoadChapter2();
		
	if (LevelIndex == 3)
		LoadChapter3();

	GI->ClearCompletedQuests();
}


void ALevelManager::InitializeGameSaveManager()
{
	GameSaveManager = GetWorld()->SpawnActor<AGameSaveManager>( AGameSaveManager::StaticClass() );
	GI = Cast<UProjectDGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );
}

void ALevelManager::LoadChapter1()
{
	AProjectDCharacter* Character = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>( UGameplayStatics::CreateSaveGameObject( UMySaveGame::StaticClass() ) );

	if (SaveGameInstance)
	{
		/** Save file data **/
		SaveGameInstance->SaveSlotName = "PlayerMainSave";
		SaveGameInstance->SaveIndex = static_cast<int32>(ESaveType::SAVE_MAIN);

		TMap<FString , int32> ItemMap;

		SaveGameInstance->SaveStruct.SaveName = "PlayerMainSave";
		SaveGameInstance->SaveStruct.LevelName = "GameLv1";
		SaveGameInstance->SaveStruct.IsUseLocation = false;

		SaveGameInstance->SaveStruct.QuickSlotKey1 = "";
		SaveGameInstance->SaveStruct.QuickSlotKey2 = "";
		SaveGameInstance->SaveStruct.QuickSlotKey3 = "";
		SaveGameInstance->SaveStruct.QuickSlotKey4 = "";

		if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass( GetWorld() , APlayerStart::StaticClass() ))
			SaveGameInstance->SaveStruct.Location = PlayerStart->GetActorLocation();


		SaveGameInstance->SaveStruct.ItemBases = ItemMap;

		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::RED , false );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::YELLOW , false );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::BLUE , false );

		TMap<int32 , bool> ToToAutoSaveData;

		ToToAutoSaveData.Add( 4000 , false );

		ToToAutoSaveData.Add( 9500 , false );
		ToToAutoSaveData.Add( 4200 , false );
		ToToAutoSaveData.Add( 9700 , false );

		ToToAutoSaveData.Add( 9800 , false );

		TArray<int32> PlayerSkillLevel;

		for(int32 i = 0; i < 6; ++i)
			PlayerSkillLevel.Add(1);

		SaveGameInstance->SaveStruct.ToToAutoSaveData = ToToAutoSaveData;
		SaveGameInstance->SaveStruct.PlayerSkillLevel = PlayerSkillLevel;

		

		bool bSuccess = UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->SaveIndex );

		if (bSuccess)
		{
			UE_LOG( LogTemp , Log , TEXT( "Game saved successfully." ) );
			UGameplayStatics::OpenLevel( GetWorld() , SaveGameInstance->SaveStruct.LevelName );
		}
		else
		{
			UE_LOG( LogTemp , Error , TEXT( "Failed to save game." ) );
		}

	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "SaveGameInstance is nullptr" ) );
	}
}

void ALevelManager::LoadChapter2()
{
	TMap<FString , int32> ItemMap;

	ItemMap.Add( L"기름" , 2 );
	ItemMap.Add( L"냉각수" , 2 );

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>( UGameplayStatics::CreateSaveGameObject( UMySaveGame::StaticClass() ) );

	if (SaveGameInstance)
	{
		SaveGameInstance->SaveSlotName = "PlayerMainSave";
		SaveGameInstance->SaveIndex = static_cast<int32>(ESaveType::SAVE_MAIN);

		SaveGameInstance->SaveStruct.ItemBases = ItemMap;

		SaveGameInstance->SaveStruct.SaveName = "PlayerMainSave";
		SaveGameInstance->SaveStruct.LevelName = "GameLv2";
		SaveGameInstance->SaveStruct.IsUseLocation = false;

		SaveGameInstance->SaveStruct.QuickSlotKey1 = L"기름";
		SaveGameInstance->SaveStruct.QuickSlotKey2 = L"냉각수";
		SaveGameInstance->SaveStruct.QuickSlotKey3 = "";
		SaveGameInstance->SaveStruct.QuickSlotKey4 = "";

		SaveGameInstance->SaveStruct.Location = FVector( 0.0 , 0.0 , 0.0 );

		TMap<int32 , bool> ToToAutoSaveData;

		ToToAutoSaveData.Add( 4000 , true );

		ToToAutoSaveData.Add( 9500 , false );
		ToToAutoSaveData.Add( 4200 , false );
		ToToAutoSaveData.Add( 9700 , false );

		ToToAutoSaveData.Add( 9800 , false );

		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::RED , true );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::YELLOW , false );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::BLUE , false );

		TArray<int32> PlayerSkillLevel;

		for (int32 i = 0; i < 6; ++i)
		{
			if(i == 0 || i == 1)
				PlayerSkillLevel.Add( 3 );
			else
				PlayerSkillLevel.Add( 1 );
		}
			

		SaveGameInstance->SaveStruct.ToToAutoSaveData = ToToAutoSaveData;
		SaveGameInstance->SaveStruct.PlayerSkillLevel = PlayerSkillLevel;

		bool bSuccess = UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->SaveIndex );

		if (bSuccess)
		{
			UE_LOG( LogTemp , Log , TEXT( "Game saved successfully." ) );
			UGameplayStatics::OpenLevel( GetWorld() , SaveGameInstance->SaveStruct.LevelName );
		}
		else
		{
			UE_LOG( LogTemp , Error , TEXT( "Failed to save game." ) );
		}

	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "SaveGameInstance is nullptr" ) );
	}

	
}

void ALevelManager::LoadChapter3()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>( UGameplayStatics::CreateSaveGameObject( UMySaveGame::StaticClass() ) );

	if (SaveGameInstance)
	{
		/** Save file data **/
		SaveGameInstance->SaveSlotName = "PlayerMainSave";
		SaveGameInstance->SaveIndex = static_cast<int32>(ESaveType::SAVE_MAIN);

		TMap<FString , int32> ItemMap;

		ItemMap.Add( L"기름" , 10 );
		ItemMap.Add( L"냉각수" , 10 );

		SaveGameInstance->SaveStruct.ItemBases = ItemMap;

		SaveGameInstance->SaveStruct.SaveName = "PlayerMainSave";
		SaveGameInstance->SaveStruct.LevelName = "GameLv3";
		SaveGameInstance->SaveStruct.IsUseLocation = false;

		SaveGameInstance->SaveStruct.QuickSlotKey1 = L"기름";
		SaveGameInstance->SaveStruct.QuickSlotKey2 = L"냉각수";
		SaveGameInstance->SaveStruct.QuickSlotKey3 = "";
		SaveGameInstance->SaveStruct.QuickSlotKey4 = "";

		SaveGameInstance->SaveStruct.Location = FVector( 0.0 , 0.0 , 0.0 );

		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::RED , true );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::YELLOW , true );
		SaveGameInstance->SaveStruct.CanUseColor.Add( EUseColor::BLUE , true );

		TMap<int32 , bool> ToToAutoSaveData;

		ToToAutoSaveData.Add( 4000 , true );

		ToToAutoSaveData.Add( 9500 , true );
		ToToAutoSaveData.Add( 4200 , true );
		ToToAutoSaveData.Add( 9700 , true );

		ToToAutoSaveData.Add( 9800 , false );

		TArray<int32> PlayerSkillLevel;

		for (int32 i = 0; i < 6; ++i)
			PlayerSkillLevel.Add( 5 );

		SaveGameInstance->SaveStruct.ToToAutoSaveData = ToToAutoSaveData;
		SaveGameInstance->SaveStruct.PlayerSkillLevel = PlayerSkillLevel;

		SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Head , L"고급 메모리 칩" );
		SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Top , L"2663년 최신형 보닛" );
		SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Pants , L"2662년 128기통 엔진" );
		SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Shoes , L"2024년 냉각장치" );
		SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Weapon , L"Sword" );

		bool bSuccess = UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->SaveIndex );

		if (bSuccess)
		{
			UE_LOG( LogTemp , Log , TEXT( "Game saved successfully." ) );
			UGameplayStatics::OpenLevel( GetWorld() , SaveGameInstance->SaveStruct.LevelName );
		}
		else
		{
			UE_LOG( LogTemp , Error , TEXT( "Failed to save game." ) );
		}

	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "SaveGameInstance is nullptr" ) );
	}
}

