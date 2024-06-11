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
	FTutorialData* GetTutorialData(int32 TutorialID);
	int32 FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex);
	void SetTutorialUI(EExplainType _ExplainType, int32 _ExplainIndex);
	
	UPROPERTY()
	class UDataTable* TutorialTable;


private:
	// 몇번째 나온 설명인지
	// ex) 0 일때 냉각수 사용방법까지 모두 설명 / 1일때는 사용하라고만 말하기
	TMap<EExplainType, int32> TutorialIndexMap;
};
