// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerTutorialComp.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Data/ItemDataStructs.h"
#include "Data/TutorialData.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"
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
	if(Player)
	{
		InventoryComp = Cast<UInventoryComponent>( Player->GetComponentByClass( UInventoryComponent::StaticClass() ) );
		PlayerFSMComp = Player->GetPlayerFSMComp();
	}

	
	// ItemIdData.Add(0, "Consumeable_001"); // 베터리
	ItemIdData.Add(ETutoItemType::COOL_WATER, TEXT("Consumeable_002")); // 냉각수
	ItemIdData.Add(ETutoItemType::OIL, TEXT("Consumeable_003")); // 오일
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
			if(_TutoData->ExplainType == EExplainType::MAIN_STORY && PlayerFSMComp->CanChangeState(EPlayerState::TALK_NPC))
			{
				PlayerFSMComp->ChangePlayerState(EPlayerState::TALK_NPC);
			}
			
			TutoData = _TutoData;
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
	if(_TutoData->ExplainType == EExplainType::MAIN_STORY)
	{
		PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);
	}
	
	// 만약 아이템을 제공하는 튜토리얼이었다면
	if(_TutoData->TutorialItem.IsGiveItem)
		Player->GetTutorialComp()->CreateItem(_TutoData->TutorialItem.GiveItem,_TutoData->TutorialItem.GiveItemQuantity);

	// 퀘스트와 연관된 튜토리얼이라면
	if(_TutoData->TutorialQuest.IsQuest)
		Player->GetTutorialComp()->StartQuest(_TutoData->TutorialQuest.QuestID);

	TutoData = nullptr;
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

