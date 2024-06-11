// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectDGameInstance.generated.h"

/**
 * 
 */

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
	void InitTutorialIndex();
	
	FPlayerSkillData* GetPlayerSkillData(int32 SkillID);
	FTutorialData* GetTutorialData(int32 TutorialID);
	
	FORCEINLINE TMap<EUseColor, bool> GetCanUseColor(){return CanUseColor;}
	FORCEINLINE void SetCanUseColor(EUseColor _Color, bool bCanUse) {CanUseColor[_Color] = bCanUse;}

	TMap<EExplainType, int32> TutorialIndexMap;

private:
	UPROPERTY()
	class UDataTable* PlayerSkillTable;

	UPROPERTY()
	TMap<EUseColor, bool> CanUseColor;

	UPROPERTY()
	class UDataTable* TutorialTable;



public:

};
