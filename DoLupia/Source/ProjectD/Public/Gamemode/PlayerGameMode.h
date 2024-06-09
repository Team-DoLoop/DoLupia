// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Library/GameSaveManager.h"
#include "PlayerGameMode.generated.h"


#define SAVE(Character, SaveType, SaveSlotName, InterfaceSaveName, LevelName, UseThread, UseLocation)					\
    ALevelManager::GetInstance(GetWorld())->SaveGame(Character, SaveType, SaveSlotName, InterfaceSaveName, LevelName,	\
    Character->GetActorLocation(), Character->GetInventory()->GetInventoryContents(), UseThread, UseLocation);

#define LOAD(SaveType, SaveSlotName, UseThread, UseLocation, OpenLevel )						\
		ALevelManager::GetInstance(GetWorld())->LoadGame (										\
		Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() ) ,	\
		SaveType , SaveSlotName , UseThread , UseLocation, OpenLevel );							\
																								\



class UAIConnectionLibrary;
class UNPCConvWidget; 
class UAITestWidget;
class ALevelManager;

enum class ESaveType;

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerGameMode();

	virtual void StartPlay() override;
	virtual void BeginPlay() override;

	class UAIConnectionLibrary* GetAIConnectionLibrary() const;

	void InitializeNPCConvWidget();
	void ReceiveNPCMsg(FString msg);

	// 2024.05.26 Player / Boss 텍스처 변경 분기처리
	void ApplyAITxtP();
	void ApplyAITxtB();

	UPROPERTY( BlueprintReadOnly )
	class UNPCConvWidget* NPCConvUI;

	UPROPERTY( BlueprintReadOnly )
	class UAITestWidget* AITestUI;


private:
	UPROPERTY()
	TArray<FName> LevelNames;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;

	/*---------- Level 별 bgm ----------*/
public:
	// 레벨에 대한 BGM을 재생하는 함수
	void PlayBGMForLevel( int32 LevelIndex );

protected:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "BGM" )
	TMap<int32 , USoundWave*> LvBGMs;

	UPROPERTY( Transient )
	USoundBase* CurrentBGM;

private:
	int32 LevelIdx;

	/*---------- Level Open ----------*/
public:
	void ChangeNextLv( FName LevelName, AProjectDCharacter* Character, ESaveType SaveType = ESaveType::SAVE_MAIN);

	/*---------- CameraBoom Setting ----------*/
public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float PlayerCameraboom = 0.0f;

	void SetPlayerCameraboom(float camboom);

	/*---------- QuestID Recieve ----------*/
public:
	// Getter 함수 선언
	UFUNCTION( BlueprintCallable , Category = "Quest" )
	int32 GetQuestID() const;

	// Setter 함수 선언
	UFUNCTION( BlueprintCallable , Category = "Quest" )
	void SetQuestID( int32 NewQuestID );

private:
	int32 questID = -1;

};
