// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerTutorialComp.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
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
	
	// ItemIdData.Add(0, "Consumeable_001"); // 베터리
	ItemIdData.Add(ETutoItemType::COOL_WATER, "Consumeable_002"); // 냉각수
	ItemIdData.Add(ETutoItemType::OIL, "Consumeable_003"); // 오일
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
		
		// 처음 들어왔다면
		if(IsFirstIndex)
		{
			DefaultUI->ChangeNextBtn(NextString);
			IsFirstIndex = false;
		}
		
		// 데이터가 마지막이라면
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
	
	if(auto _TutoData = GI->GetTutorialData(TutorialID))
	{
		SetTutorialUI(_TutoData);
	}
	else
	{
		// 종료되게 + 아이템 제공? + 퀘스트 연관?
		EndTutorial(_TutoData);
	}
}

void UPlayerTutorialComp::EndTutorial(FTutorialData* _TutoData)
{
	if(!DefaultUI) return;
	
	IsFirstIndex = true;
	TutorialID = 0;
	DefaultUI->HideTutorialWidget();

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
	
}


// <----------------------------- Item ----------------------------->

void UPlayerTutorialComp::CreateItem(ETutoItemType _TutoItemType, int32 _Quantity)
{
	FName _DesiredItemID = ItemIdData[_TutoItemType];
	if (ItemDataTable && !_DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>( _DesiredItemID , _DesiredItemID.ToString() );

		UItemBase* ItemReference = NewObject<UItemBase>( this , UItemBase::StaticClass() );

		ItemReference->SetID( ItemData->ID );
		ItemReference->SetItemType( ItemData->ItemType );
		ItemReference->SetItemQuality( ItemData->ItemQuality );
		ItemReference->SetItemStatistics( ItemData->ItemStatistics );
		ItemReference->SetTextData( ItemData->TextData );
		ItemReference->SetNumericData( ItemData->NumericData );
		ItemReference->SetAssetData( ItemData->AssetData );
		ItemReference->SetItemSkillColorData( ItemData->ItemSkillColor );

		// 만약 MaxStacksize 가 1보다 작다면 인벤토리에 쌓이지 않게 한다.
		FItemNumericData& ItemNumericData = ItemReference->GetNumericData();
		ItemNumericData.bIsStackable = ItemNumericData.MaxStackSize > 1;
		_Quantity <= 0 ? ItemReference->SetQuantity( 1, false ) : ItemReference->SetQuantity( _Quantity, false );
	}
}

