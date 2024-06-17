// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerTutorialComp.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Components/InventoryComponent.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Data/ItemDataStructs.h"
#include "Data/TutorialData.h"
#include "Gamemode/PlayerGameMode.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
#include "Pooling/SoundManager.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"

class UItemBase;
// Sets default values for this component's properties
UPlayerTutorialComp::UPlayerTutorialComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerTutorialComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Player = Cast<AProjectDCharacter>(GetOwner());
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GM = Cast<APlayerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(Player)
	{
		InventoryComp = Cast<UInventoryComponent>( Player->GetComponentByClass( UInventoryComponent::StaticClass() ) );
		PlayerFSMComp = Player->GetPlayerFSMComp();
	}

	
	ItemIdData.Add(ETutoItemType::COOL_WATER, TEXT("Consumeable_002")); // 냉각수
	ItemIdData.Add(ETutoItemType::OIL, TEXT("Consumeable_003")); // 오일
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
	// ItemIdData.Add(0, "Consumeable_001"); // 배터리
}


// Called every frame
void UPlayerTutorialComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



// <----------------------------- Tutorial UI ----------------------------->

void UPlayerTutorialComp::SetTutorialUI(FTutorialData* _TutoData)
{
	if(DefaultUI)
	{
		if(!_TutoData) return;
		
		UE_LOG(LogTemp, Log, TEXT("SetTutorialUI : %d"), ExplainIndex);
		
		// 처음 들어왔다면
		if(ExplainIndex == 0)
		{			
			// DefaultUI->ChangeNextBtn(NextString);
			if(_TutoData->bCantActing && PlayerFSMComp->CanChangeState(EPlayerState::TALK_NPC))
			{
				PlayerFSMComp->ChangePlayerState(EPlayerState::TALK_NPC);
			}
			
			TutoData = _TutoData;

			// 사운드 시작
			if(ToToSFX)
				ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( ToToSFX , ENPCSound::NPCSound1 , 0.25f );

		}
		
		DefaultUI->ShowTutorialWidget(_TutoData, ExplainIndex);
	}
}

void UPlayerTutorialComp::PressNextTutorial()
{
	// 버튼 누른 경우 UI 세팅 -> 만약 두번째 눌렀다면 UI 에서 NextTutorial() 호출 -> ShowTutorialWidget
	if(!GI || !TutoData) return;
	
	// auto _TutoData = GI->GetTutorialData(TutorialID);
	DefaultUI->NextTutorial();
}

void UPlayerTutorialComp::NextTutorial()
{
	if(!TutoData) return;
	
	ExplainIndex = ExplainIndex + 1;
	if(TutoData->TutorialWidgetData.StoryExplainText.Num() == ExplainIndex)
	{
		EndTutorial(TutoData);
		return;
	}

	DefaultUI->ShowTutorialWidget(TutoData, ExplainIndex);
}

void UPlayerTutorialComp::EndTutorial(FTutorialData* _TutoData)
{
	if(!DefaultUI) return;
	
	ExplainIndex = -1;
	DefaultUI->HideTutorialWidget();

	if(!_TutoData) return;
	
	// MAIN_STORY 였다면 Idle로 돌려놓기
	if(_TutoData->bCantActing)
	{
		PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);
	}
	
	// 만약 아이템을 제공하는 튜토리얼이었다면
	if(_TutoData->TutorialItem.IsGiveItem)
		CreateItem(_TutoData->TutorialItem.GiveItem,_TutoData->TutorialItem.GiveItemQuantity);

	// 퀘스트와 연관된 튜토리얼이라면
	if(_TutoData->TutorialQuest.IsQuest)
		StartQuest(_TutoData->TutorialQuest.QuestID);

	// 트리거 관련된 튜토리얼이라면
	if(_TutoData->TutorialTrigger.IsTrigger)
		StartTrigger(_TutoData->TutorialTrigger.TriggerID);
	
	TutoData = nullptr;
	IsTotoSaying = false;
}


// <----------------------------- Quest ----------------------------->

void UPlayerTutorialComp::StartQuest(int32 _QuestID)
{
	if(!GI) return;
	
	GI->GiveQuest(_QuestID);
}


// <----------------------------- Item ----------------------------->

void UPlayerTutorialComp::CreateItem(ETutoItemType _TutoItemType, int32 _Quantity)
{
	if(!GI) return;
	FString _DesiredItemID = ItemIdData[_TutoItemType];
	auto ItemData = GI->GetItemData(_DesiredItemID);
	if (ItemData)
	{
		UE_LOG(LogTemp, Log, TEXT("PlayerTuto Create Item : %s"), *_DesiredItemID);
		
		UItemBase* ItemReference = NewObject<UItemBase>( this , UItemBase::StaticClass() );

		ItemReference->CreateItemCopy(ItemData, _Quantity);
		InventoryComp->HandelAddItem( ItemReference);
	}
}


// <----------------------------- Trigger ----------------------------->

void UPlayerTutorialComp::StartTrigger(int32 _TriggerID)
{
	// 포탈
	if(_TriggerID == 1)
	{
		GM->ActiveLvTrigger();
	}

	// 맵2 연출
	else if(_TriggerID == 2)
	{
		GM->HandleIntrusionEvent();
		
		// 뭔가 있다는 토토 대사 시작( 연출 끝나면 들어갈 부분. 지금은 임시로 넣어둠)
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer( TimerHandle , this , &UPlayerTutorialComp::ExecuteTutorial , 2.0f , false );
		
	}
}

void UPlayerTutorialComp::ExecuteTutorial()
{
	GI->ExecuteTutorial(EExplainType::MAIN_STORY, -1, 9500);
}

