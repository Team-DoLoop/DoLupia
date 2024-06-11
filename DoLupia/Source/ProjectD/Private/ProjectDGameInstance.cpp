// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDGameInstance.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerTutorialComp.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Data/TutorialData.h"
#include "Kismet/GameplayStatics.h"

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

void UProjectDGameInstance::GetTutorialData(EExplainType _ExplainType)
{
	// 데이터 가져오기
	int32 _TutorialID = FindTutorialID(_ExplainType, TutorialIndexMap[_ExplainType]);
	auto TutoData = TutorialTable->FindRow<FTutorialData>(*FString::FromInt(_TutorialID), TEXT(""));
	
	// 데이터가 있다면
	if(!TutoData) return;
	
	// 확인했다고 튜토리얼임을 저장
	TutorialIndexMap[TutoData->ExplainType]++;

	// 튜토리얼 관리하는 플레이어 컴포넌트 소환해서 UI 세팅해주기
	AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->GetTutorialComp()->SetTutorialUI(TutoData);
}

int32 UProjectDGameInstance::FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex)
{
	return (static_cast<int32>(_ExplainType) * 1000) + (_ExplainIndex * 100);
}
