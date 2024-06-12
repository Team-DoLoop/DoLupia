// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerTutorialComp.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
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

		TutoData = _TutoData;
		
		// 처음 들어왔다면
		if(IsFirstIndex)
		{
			DefaultUI->ChangeNextBtn(NextString);
			IsFirstIndex = false;
		}
		
		// 다음 데이터가 마지막이라면
		if(_TutoData->NextIndex == -1)
		{
			DefaultUI->ChangeNextBtn(CloseString);
			
		}
		
		DefaultUI->ShowTutorialWidget(_TutoData);
		TutorialID = _TutoData->NextIndex;
	}
}

void UPlayerTutorialComp::NextTutorial()
{
	if(!GI || TutorialID == 0) return;
	
	if(TutorialID == -1)
	{
		EndTutorial(TutoData);
		return;
	}
	
	auto _TutoData = GI->GetTutorialData(TutorialID);
	if(_TutoData)
	{
		SetTutorialUI(_TutoData);
	}
}

void UPlayerTutorialComp::EndTutorial(FTutorialData* _TutoData)
{
	if(!DefaultUI) return;
	
	IsFirstIndex = true;
	TutorialID = 0;
	DefaultUI->HideTutorialWidget();

	if(!_TutoData) return;
	
	// 만약 아이템을 제공하는 튜토리얼이었다면
	if(_TutoData->TutorialItem.IsGiveItem)
		Player->GetTutorialComp()->CreateItem(_TutoData->TutorialItem.GiveItem,_TutoData->TutorialItem.GiveItemQuantity);

	// 퀘스트와 연관된 튜토리얼이라면
	if(_TutoData->TutorialQuest.IsQuest)
		Player->GetTutorialComp()->StartQuest(_TutoData->TutorialQuest.QuestID);
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

