// Fill out your copyright notice in the Description page of Project Settings.


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
