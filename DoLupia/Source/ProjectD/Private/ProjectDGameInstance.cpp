// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDGameInstance.h"
#include "Data/PlayerSkillDataStructs.h"

UProjectDGameInstance::UProjectDGameInstance()
{
	FString PlayerSkillDataPath = TEXT("/Script/Engine.DataTable'/Game/Player/Data/DT_PlayerSkill.DT_PlayerSkill'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerSkill(*PlayerSkillDataPath);
	PlayerSkillTable = DT_PlayerSkill.Object;
}

void UProjectDGameInstance::Init()
{
	Super::Init();
}

FPlayerSkillData* UProjectDGameInstance::GetPlayerSkillData(int32 SkillID)
{
	if(!PlayerSkillTable) return nullptr;

	return PlayerSkillTable->FindRow<FPlayerSkillData>(*FString::FromInt(SkillID), TEXT(""));
}
