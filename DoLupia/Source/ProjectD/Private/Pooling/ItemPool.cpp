// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling/ItemPool.h"
#include "Items/ItemBase.h"

UItemPool::UItemPool()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTable( TEXT( "/Game/Item/ItemData/MundaneItems" ) );

	if (DataTable.Succeeded())
    {
        ItemDataTable = DataTable.Object;

		ItemManager.Empty();

		if (ItemDataTable)
		{
			TArray<FItemData*> OutRowArray;
			ItemDataTable->GetAllRows<FItemData>( TEXT( "Context String" ) , OutRowArray );

			for (FItemData* ItemData : OutRowArray)
			{
				if (ItemData)
				{

					ItemManager.Emplace( ItemData->TextData.Name.ToString() , *ItemData );
				}
			}
		}
    }


}

void UItemPool::CreateItem(int32 NumberOfCreate)
{
    //for (int32 i = 0; i < NumberOfCreate; ++i)
    //{
    //    UItemBase* Item = NewObject<UItemBase>( this, UItemBase::StaticClass() );
    //    Pool.Add(Item);
    //}

}

UItemBase* UItemPool::GetItem(const FString& ItemID)
{
    UItemBase* RetrievedItem = NewObject<UItemBase>( this , UItemBase::StaticClass() );
	
	FItemData ItemData = *ItemManager.Find(ItemID);

	RetrievedItem->SetID( ItemData.ID );
	RetrievedItem->SetItemType( ItemData.ItemType );
	RetrievedItem->SetItemQuality( ItemData.ItemQuality );
	RetrievedItem->SetItemStatistics( ItemData.ItemStatistics );
	RetrievedItem->SetTextData( ItemData.TextData );
	RetrievedItem->SetNumericData( ItemData.NumericData );
	RetrievedItem->SetAssetData( ItemData.AssetData );
	RetrievedItem->SetItemSkillColorData( ItemData.ItemSkillColor );
	RetrievedItem->SetItemMaterial( ItemData.ItemMaterial );

	// 만약 MaxStacksize 가 1보다 작다면 인벤토리에 쌓이지 않게 한다.
	FItemNumericData& ItemNumericData = ItemData.NumericData;
	ItemNumericData.bIsStackable = ItemNumericData.MaxStackSize > 1;

    return RetrievedItem; // 풀에서 객체 꺼내기
}

void UItemPool::ReturnItem( UItemBase* InItem )
{
    if (InItem != nullptr && Pool.Num() < 10000)
    {
        Pool.Add(InItem); // 아이템 반환
    }
}
