// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectDGameInstance.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerTutorialComp.h"
#include "Data/ItemDataStructs.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Data/TutorialData.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/Struct_QuestSystem.h"
#include "Quest/QuestLogComponent.h"

UProjectDGameInstance::UProjectDGameInstance()
{
	FString PlayerSkillDataPath = TEXT("/Script/Engine.DataTable'/Game/Player/Data/DT_PlayerSkill.DT_PlayerSkill'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PlayerSkill(*PlayerSkillDataPath);
	if(DT_PlayerSkill.Succeeded())
	{
		PlayerSkillTable = DT_PlayerSkill.Object;
	}

	FString TutorialDataPath = TEXT("/Script/Engine.DataTable'/Game/Tutorial/Data/DT_Tutorial.DT_Tutorial'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Tutorial(*TutorialDataPath);
	if(DT_Tutorial.Succeeded())
	{
		TutorialTable = DT_Tutorial.Object;
	}

	FString QuestDataPath = TEXT("/Script/Engine.DataTable'/Game/QuestSystem/Data/QuestDataTable.QuestDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Quest(*QuestDataPath);
	if(DT_Quest.Succeeded())
	{
		QuestTable = DT_Quest.Object;
	}
	
	FString ItemDataPath = TEXT("/Script/Engine.DataTable'/Game/Item/ItemData/MundaneItems.MundaneItems'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Item(*ItemDataPath);
	if(DT_Item.Succeeded())
	{
		ItemTable = DT_Item.Object;
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

FTutorialData* UProjectDGameInstance::GetTutorialData(int32 _TutorialID)
{
	return TutorialTable->FindRow<FTutorialData>(*FString::FromInt(_TutorialID), TEXT(""));
}

void UProjectDGameInstance::ExecuteTutorial(EExplainType _ExplainType)
{
	// 첫 데이터 찾기
	TutorialID = FindTutorialID(_ExplainType, TutorialIndexMap[_ExplainType]);
	FTutorialData* TutoData = GetTutorialData(TutorialID);
	
	// 데이터가 있다면
	if(!TutoData) return;
	
	// 확인했다고 튜토리얼임을 저장
	TutorialIndexMap[TutoData->ExplainType] = TutoData->ExplainIndex;

	// 튜토리얼 관리하는 플레이어 컴포넌트 소환해서 UI 세팅해주기
	if(AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if(auto PlayerTuto = Player->GetTutorialComp())
		{
			PlayerTuto->SetTutorialID(TutorialID);
			PlayerTuto->SetTutorialUI(TutoData);
		}
	}
}

int32 UProjectDGameInstance::FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex)
{
	return (static_cast<int32>(_ExplainType) * 1000) + (_ExplainIndex * 100);
}


// <----------------------------- Quest ----------------------------->

FQuestDetails* UProjectDGameInstance::GetQuestData(int32 _QuestID)
{
	return QuestTable->FindRow<FQuestDetails>(*FString::FromInt(_QuestID), TEXT(""));
}

void UProjectDGameInstance::GiveQuest(int32 _QuestID)
{
	if (AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		FName _QuestIdName = FName(*FString::FromInt(_QuestID));
		UQuestLogComponent* QuestComp = Player->GetQuestLogComponent();

		bool ActiveQuest = QuestComp->QueryActiveQuest(_QuestIdName);
		if (!ActiveQuest) {
			auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

			//겜모에 퀘스트 아이디 string 로 넘김.
			gm->SetStringQuestID( _QuestIdName.ToString() );
			QuestComp->AddNewQuest( _QuestIdName );
		}
	}
}


// <----------------------------- Item ----------------------------->

FItemData* UProjectDGameInstance::GetItemData(FString ItemID)
{
	return ItemTable->FindRow<FItemData>(FName(*ItemID), TEXT(""));
}