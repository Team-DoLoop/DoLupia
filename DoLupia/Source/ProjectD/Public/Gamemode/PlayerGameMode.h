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
class USpringArmComponent;
class UTimelineComponent;
class UCurveFloat;
class AProjectDCharacter;
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

	UAIConnectionLibrary* GetAIConnectionLibrary() const;

	// 2024.05.26 Player / Boss 텍스처 변경 분기처리
	void ApplyAITxtP();
	void ApplyAITxtB();

private:
	UPROPERTY()
	class UProjectDGameInstance* GI;

	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	TArray<FName> LevelNames;

	int32 LevelIdx;

	UPROPERTY( EditDefaultsOnly )
	UAIConnectionLibrary* AIlib;

	/*---------- Level 별 bgm ----------*/
public:
	// 레벨에 대한 BGM을 재생하는 함수
	void PlayBGMForLevel( int32 LevelIndex );

protected:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "BGM" )
	TMap<int32 , USoundWave*> LvBGMs;

	UPROPERTY( Transient )
	USoundBase* CurrentBGM;

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

	UFUNCTION( BlueprintCallable , Category = "Quest" )
	void SetQuestID( int32 NewQuestID );

	UFUNCTION( BlueprintCallable , Category = "Quest" )
	FString GetStringQuestID();

	UFUNCTION( BlueprintCallable , Category = "Quest" )
	void SetStringQuestID( FString QuestID );

	UFUNCTION( BlueprintCallable , Category = "Quest" )
	FString GetNxtQuestID() const;

	UFUNCTION( BlueprintCallable , Category = "Quest" )
	void SetNxtQuestID( FString nextquestID );

	FString FStringQuestID = "";

	void HandleIntrusionEvent();
	void StartGameStory();

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	bool IsToToNotInMapStart;

private:
	int32 questID = -1;
	FString NextquestID ;

	/*---------- Level Location Title Widget --------*/

public:

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class ULocationTitleWidget> LocationFactory;

	void CreateLocationTitleWidget(int32 currentlevel);

	/*---------- Level Portal Trigger --------*/
	void ActiveLvTrigger();

	/*---------- Camera lerp --------*/
public:
	void LerpPlayerCameraLength( float NewTargetArmLength );

private:
	UPROPERTY()
	USpringArmComponent* CameraBoom;

	// lerp 적용
	UPROPERTY()
	UTimelineComponent* TimelineComp;

	float InitialArmLength;
	float NewTargetArmLength;

	UFUNCTION()
	void HandleTimelineProgress( float Value );

	UFUNCTION()
	void OnTimelineFinished();

	UPROPERTY( EditAnywhere , Category = "Timeline" )
	UCurveFloat* PlayerCamCurve;

	/*---------- Quest, Dialog <> NPC, Minigame --------*/
private:
	void FindNextNPC();
	void FindMiniGame();


	/*---------- Quest Location actor  --------*/
public:
	void ActivateMarkers(int32 MarkerID);
};
