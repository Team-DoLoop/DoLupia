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
	
	FPlayerSkillData* GetPlayerSkillData(int32 SkillID);
	
	FORCEINLINE TMap<EUseColor, bool> GetCanUseColor(){return CanUseColor;}
	FORCEINLINE void SetCanUseColor(EUseColor _Color, bool bCanUse) {CanUseColor[_Color] = bCanUse;}

private:
	UPROPERTY()
	class UDataTable* PlayerSkillTable;

	UPROPERTY()
	TMap<EUseColor, bool> CanUseColor;



	// <------------------ Tutorial ------------------>
public:
	void InitTutorialIndex();
	void GetTutorialData(EExplainType _ExplainType);
	int32 FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex);
	
	UPROPERTY()
	class UDataTable* TutorialTable;


private:
	// 몇번 확인했는지 저장 / 만약 DataTable의 Index와 다르면 return
	TMap<EExplainType, int32> TutorialIndexMap;
};
