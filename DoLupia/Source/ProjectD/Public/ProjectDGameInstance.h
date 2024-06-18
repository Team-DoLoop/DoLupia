// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/TutorialData.h"
#include "Engine/GameInstance.h"
#include "ProjectDGameInstance.generated.h"

/**
 * 
 */

struct FItemData;
struct FQuestDetails;
enum class EExplainType : uint8;
enum class EUseColor : uint8;
struct FPlayerSkillData;
struct FTutorialData;
UCLASS()
class PROJECTD_API UProjectDGameInstance : public UGameInstance
{
	GENERATED_BODY()


	// <------------------ Player Skill ------------------>
public:
	UProjectDGameInstance();

	virtual void Init() override;
	void InitCanUseColor();
	void InitPlayerSkillLevel();
	
	FPlayerSkillData* GetPlayerSkillData(int32 SkillID);
	
	FORCEINLINE TMap<EUseColor, bool> GetCanUseColor(){return CanUseColor;}
	FORCEINLINE void SetCanUseColor(EUseColor _Color, bool bCanUse) {CanUseColor[_Color] = bCanUse;}

	void SetPlayerSkillLevel(EUseColor _Color, int32 _SkillKeyIndex, int32 SkillLevel);
	FORCEINLINE TArray<int32> GetPlayerSkillLevel(){return PlayerSkillLevel;}

private:
	UPROPERTY()
	class UDataTable* PlayerSkillTable;

	UPROPERTY()
	TMap<EUseColor, bool> CanUseColor;

	TArray<int32> PlayerSkillLevel;



	// <------------------ Tutorial ------------------>
public:
	void InitTutorialIndex();
	void InitToToAutoSaveData();
	int32 FindLastToToSaveData(int32 _MapIndex);
	FTutorialData* GetTutorialData(int32 _TutorialID);
	void ExecuteTutorial(EExplainType _ExplainType, int32 _Index = -1, int32 _TutorialID = -1);
	int32 FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex);
	
	FORCEINLINE int32 GetTutorialID() const { return TutorialID; }

private:
	TMap<int32, bool> ToToAutoSaveData;
	
	UPROPERTY()
	class UDataTable* TutorialTable;
	
	int32 TutorialID;
	
	// 몇번 확인했는지 저장 / 만약 DataTable의 Index와 다르면 return
	TMap<EExplainType, int32> TutorialIndexMap;

	

	// <------------------ Quest ------------------>
public:
	FQuestDetails* GetQuestData(int32 _QuestID);
	FQuestDetails* GetQuestData(FString _QuestID);
	FQuestDetails* GetQuestData(FName _QuestID);
	void GiveQuest(int32 _QuestID);

	void InitCompletedQuests();
	FORCEINLINE TArray<FName> GetCompletedQuest() { return CompletedQuests; }
	FORCEINLINE void SetCompletedQuest( FName CompletedQuestID ) { CompletedQuests.Add(CompletedQuestID); }


	TArray<FName> CompletedQuests;

private:
	
	UPROPERTY()
	class UDataTable* QuestTable;

	// <------------------ Item ------------------>
public:
	FItemData* GetItemData(FString ItemID);

private:
	UPROPERTY()
	class UDataTable* ItemTable;


	// <------------------ PlayerLocation ------------------>
public:
	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Save" )
	FVector PlayerRestartLocation;

	//UFUNCTION( BlueprintCallable , Category = "Save" )
	//void LoadPlayerLocation();
	//
};
