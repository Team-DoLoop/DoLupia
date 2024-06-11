// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerTutorialComp.h"

#include "Data/ItemDataStructs.h"
#include "Data/TutorialData.h"
#include "Items/ItemBase.h"

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
	ItemIdData.Add(0, "Consumeable_001"); // 베터리
	ItemIdData.Add(1, "Consumeable_002"); // 냉각수
	ItemIdData.Add(2, "Consumeable_003"); // 오일
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
	
	
}


// <----------------------------- Quest ----------------------------->

void UPlayerTutorialComp::CreateItem( int32 _ItemNum, int32 _Quantity)
{
	FName _DesiredItemID = ItemIdData[_ItemNum];
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

