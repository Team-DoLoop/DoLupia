// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDGameInstance.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Data/TutorialData.h"

UProjectDGameInstance::UProjectDGameInstance()
{
	FString PlayerSkillDataPath = TEXT("/Script/Engine.DataTable'/Game/Player/Data/DT_PlayerSkill.DT_PlayerSkill'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerSkill(*PlayerSkillDataPath);
	if(DT_PlayerSkill.Succeeded())
	{
		PlayerSkillTable = DT_PlayerSkill.Object;
	}

	FString TutorialDataPath = TEXT("/Script/Engine.DataTable'/Game/Player/Data/DT_PlayerSkill.DT_PlayerSkill'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Tutorial(*TutorialDataPath);
	if(DT_Tutorial.Succeeded())
	{
		TutorialTable = DT_Tutorial.Object;
	}
}

void UProjectDGameInstance::Init()
{
	Super::Init();
	
	InitCanUseColor();
	InitTutorialIndex();
}

// <----------------------------- Player Skill ----------------------------->

void UProjectDGameInstance::InitCanUseColor()
{
	UEnum* ColorEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUseColor"), true);
	if(!ColorEnum) return;

	for(int i = 0; i < ColorEnum->NumEnums(); i++)
	{
		CanUseColor.Add(static_cast<EUseColor>(ColorEnum->GetValueByIndex(i)), false);
	}
}

FPlayerSkillData* UProjectDGameInstance::GetPlayerSkillData(int32 SkillID)
{
	return PlayerSkillTable->FindRow<FPlayerSkillData>(*FString::FromInt(SkillID), TEXT(""));
}


// <----------------------------- Tutorial ----------------------------->

void UProjectDGameInstance::InitTutorialIndex()
{
	UEnum* ExplainType = FindObject<UEnum>(ANY_PACKAGE, TEXT("EExplainType"), true);

	if(!ExplainType) return;
	for(int i = 0; i < ExplainType->NumEnums(); i++)
	{
		TutorialIndexMap.Add(static_cast<EExplainType>(ExplainType->GetValueByIndex(i)), 0);
	}
}

FTutorialData* UProjectDGameInstance::GetTutorialData(int32 TutorialID)
{
	return TutorialTable->FindRow<FTutorialData>(*FString::FromInt(TutorialID), TEXT(""));
}

int32 UProjectDGameInstance::FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex)
{
	return (static_cast<int32>(_ExplainType) * 1000) + (_ExplainIndex * 100);
}

void UProjectDGameInstance::SetTutorialUI(EExplainType _ExplainType, int32 _ExplainIndex)
{
	// 데이터 가져오기
	int32 _TutorialID = FindTutorialID(_ExplainType, _ExplainIndex);

	// 확인했던 튜토리얼이라고 알려주기

	
	// 튜토리얼 UI를 보여주는 부분
}
