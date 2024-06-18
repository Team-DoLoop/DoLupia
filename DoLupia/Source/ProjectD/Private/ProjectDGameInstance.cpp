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
	InitCompletedQuests();
	InitToToAutoSaveData();
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

void UProjectDGameInstance::InitToToAutoSaveData()
{
	ToToAutoSaveData.Add(3000, false);	// Map Tutorial - 공격 튜토리얼 끝나고 저장
	
	ToToAutoSaveData.Add(4000, false);	// Map1 - Red 얻고 나서 저장
	
	ToToAutoSaveData.Add(9500, false);	// Map2 - 적군의 침입 시작 전 저장
	ToToAutoSaveData.Add(4200, false);	// Map2 - 슬픔 얻고 저장
	ToToAutoSaveData.Add(9700, false);	// Map2 - 마지막 포탈 가기 전 몬스터 다 잡으면 저장

	ToToAutoSaveData.Add(9800, false);	// Map3 - 맵 들어오고 토토 말 다 끝나면 저장
}

int32 UProjectDGameInstance::FindLastToToSaveData(int32 _MapIndex)
{
	
	switch (_MapIndex)
	{
	case 0 : if(ToToAutoSaveData[3000]) return 3000;
	case 1:
		{
			if(ToToAutoSaveData[4000]) return 4000;
		}
	case 2:
		{
			if(ToToAutoSaveData[9700]) return 9700;
			if(ToToAutoSaveData[4200]) return 4200;
			if(ToToAutoSaveData[9500]) return 9500;
		}
	case 3:
		{
			if(ToToAutoSaveData[9800]) return 9800;
		}
	}

	return -1;
}

FTutorialData* UProjectDGameInstance::GetTutorialData(int32 _TutorialID)
{
	return TutorialTable->FindRow<FTutorialData>(*FString::FromInt(_TutorialID), TEXT(""));
}

void UProjectDGameInstance::ExecuteTutorial(EExplainType _ExplainType, int32 _Index, int32 _TutorialID)
{
	// 첫 데이터 찾기
	if(_Index != -1) TutorialIndexMap[_ExplainType] = _Index;
	UE_LOG(LogTemp, Log, TEXT("TutorialIndexMap1 : %d "), TutorialIndexMap[_ExplainType]);

	if(_TutorialID != -1) TutorialID = _TutorialID;
	else TutorialID = FindTutorialID(_ExplainType, TutorialIndexMap[_ExplainType]);
	FTutorialData* TutoData = GetTutorialData(TutorialID);
	UE_LOG(LogTemp, Log, TEXT("TutorialID : %d"), TutorialID);
	
	// 데이터가 없다면
	if(!TutoData) return;
	
	// 튜토리얼 관리하는 플레이어 컴포넌트 소환해서 UI 세팅해주기
	if(AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if(auto PlayerTuto = Player->GetTutorialComp())
		{
			// 자동 저장하는 튜토리얼이고 Map에 있는 인덱스라면
			if(TutoData->bIsAutoSave && ToToAutoSaveData.Contains(TutorialID))
			{
				// 재시작 시에는 토토가 나오지 않게
				if(ToToAutoSaveData[TutorialID])
				{
					if(TutoData->TutorialQuest.IsQuest) GiveQuest(TutoData->TutorialQuest.QuestID);
					return;
				}

				ToToAutoSaveData[TutorialID] = true;
			}
			
			// 지금 요청한 튜토리얼이 메인 퀘스트 관련이 아닌데, 이미 말하는 중이라면
			if(!PlayerTuto->IsCantMoveToToSaying(TutoData) && PlayerTuto->GetToToSaying())
			{
				// 원래 말하던거 실행하게
				return;
			}
			UE_LOG(LogTemp, Log, TEXT("GetTutorialComp Success"));

			PlayerTuto->SetExplainIndex(0);

			PlayerTuto->SetTotoSaying(true);
			PlayerTuto->SetTutorialUI(TutoData);
		}
	}
	
	// 반복 튜토리얼의 마지막이 아니라면 확인한 튜토리얼임을 저장
	if(!TutoData->bIsTypeEnd)
	TutorialIndexMap[TutoData->ExplainType] = TutoData->ExplainIndex + 1;

	UE_LOG(LogTemp, Log, TEXT("TutorialIndexMap2 : %d "), TutorialIndexMap[_ExplainType]);
}

int32 UProjectDGameInstance::FindTutorialID(EExplainType _ExplainType, int32 _ExplainIndex)
{
	return (static_cast<int32>(_ExplainType) * 1000) + (_ExplainIndex * 100);
}


// <----------------------------- Quest ----------------------------->

FQuestDetails* UProjectDGameInstance::GetQuestData(int32 _QuestID)
{
	return QuestTable->FindRow<FQuestDetails>(*FString::Printf(TEXT("%04d"), _QuestID), TEXT(""));
}

FQuestDetails* UProjectDGameInstance::GetQuestData(FString _QuestID)
{
	return QuestTable->FindRow<FQuestDetails>(FName(*_QuestID), TEXT(""));
}

FQuestDetails* UProjectDGameInstance::GetQuestData(FName _QuestID)
{
	return QuestTable->FindRow<FQuestDetails>(_QuestID, TEXT(""));
}


void UProjectDGameInstance::GiveQuest(int32 _QuestID)
{
	if (AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		FName _QuestIdName = FName(*FString::Printf(TEXT("%04d"), _QuestID));
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

void UProjectDGameInstance::InitCompletedQuests()
{

	AProjectDCharacter* Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
	if (!Player)
	{
		UE_LOG( LogTemp , Error , TEXT( "Player is null in InitCompletedQuests" ) );
		return;
	}

	UQuestLogComponent* QuestComp = Player->GetQuestLogComponent();
	if (!QuestComp)
	{
		UE_LOG( LogTemp , Error , TEXT( "QuestComp is null in InitCompletedQuests" ) );
		return;
	}

	if (!GetCompletedQuest().IsEmpty())
	{
		for (const auto& CompletedQuestID : CompletedQuests)
		{
			QuestComp->CompletedQuests.Add(CompletedQuestID);
			UE_LOG( LogTemp , Error , TEXT( "QuestComp->CompletedQuests.Add(CompletedQuestID);" ) );
		}
	}
}


// <----------------------------- Item ----------------------------->

FItemData* UProjectDGameInstance::GetItemData(FString ItemID)
{
	return ItemTable->FindRow<FItemData>(FName(*ItemID), TEXT(""));
}


/*//<-----------------------------  Player location  ----------------------------->
void UProjectDGameInstance::LoadPlayerLocation()
{
	AProjectDCharacter* Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	//겜모에 저장된 현재 아이디를 가져와서 그 위치 값을 가져와서 play
	FString CurrnetQuestID = gm->GetStringQuestID();
	PlayerRestartLocation = GetQuestData( CurrnetQuestID )->PlayerLocation;
	Player->SetActorLocation( PlayerRestartLocation );
}
*/