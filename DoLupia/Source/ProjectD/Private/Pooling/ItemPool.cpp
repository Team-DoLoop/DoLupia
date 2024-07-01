﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling/ItemPool.h"

#include "ProjectDGameInstance.h"
#include "Items/ItemBase.h"
#include "Kismet/GameplayStatics.h"

UItemPool::UItemPool()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTable( TEXT( "/Game/Item/ItemData/MundaneItems" ) );

	if (DataTable.Succeeded())
    {
        ItemDataTable = DataTable.Object;

        if (ItemDataTable)
        {
            TArray<FItemData*> OutRowArray;
            ItemDataTable->GetAllRows<FItemData>( TEXT( "Context String" ) , OutRowArray );

            for (FItemData* ItemData : OutRowArray)
            {
                if (ItemData)
                {
                    ItemDataArray.Add( *ItemData );
                }
            }
        }
    }


}

void UItemPool::CreateItem(int32 NumberOfCreate)
{
<<<<<<< Updated upstream
    //for (int32 i = 0; i < NumberOfCreate; ++i)
    //{
    //    UItemBase* Item = NewObject<UItemBase>( this, UItemBase::StaticClass() );
    //    Pool.Add(Item);
    //}

=======


  /*  GetWorld()->GetTimerManager().SetTimerForNextTick( [this]()
    {*/
        for (FItemData ItemData : ItemDataArray)
        {
            UItemBase* ItemReference = NewObject<UItemBase>( this , UItemBase::StaticClass() );

            ItemReference->SetID( ItemData.ID );
            ItemReference->SetItemType( ItemData.ItemType );
            ItemReference->SetItemQuality( ItemData.ItemQuality );
            ItemReference->SetItemStatistics( ItemData.ItemStatistics );
            ItemReference->SetTextData( ItemData.TextData );
            ItemReference->SetNumericData( ItemData.NumericData );
            ItemReference->SetAssetData( ItemData.AssetData );
            ItemReference->SetItemSkillColorData( ItemData.ItemSkillColor );
            ItemReference->SetItemMaterial( ItemData.ItemMaterial );

            // 만약 MaxStacksize 가 1보다 작다면 인벤토리에 쌓이지 않게 한다.
            FItemNumericData& ItemNumericData = ItemReference->GetNumericData();
            ItemNumericData.bIsStackable = ItemNumericData.MaxStackSize > 1;

            ItemManager.Emplace( ItemData.TextData.Name.ToString() , ItemReference );
        }
    //} );

    //for (int32 i = 0; i < NumberOfCreate; ++i)
    //{
    //    UItemBase* Item = NewObject<UItemBase>( this, UItemBase::StaticClass() );
    //    Pool.Add(Item);
    //}
>>>>>>> Stashed changes
}

UItemBase* UItemPool::GetItem(const FString& ItemID)
{
    UItemBase* RetrievedItem = NewObject<UItemBase>( this , UItemBase::StaticClass() );
    RetrievedItem->CreateItemCopy( Cast<UProjectDGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) )->GetItem( ItemID )); 
    return RetrievedItem; // 풀에서 객체 꺼내기

}

void UItemPool::ReturnItem( UItemBase* InItem )
{
    if (InItem != nullptr && Pool.Num() < 10000)
    {
        Pool.Add(InItem); // 아이템 반환
    }
}
