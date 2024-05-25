
#include "Spawner/ItemSpawner.h"

#include "Items/ItemBase.h"
#include "Pooling/ItemPool.h"
#include "Library/BezierMovementLibrary.h"
#include "World/DroppedItem.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

    ItemPool = CreateDefaultSubobject<UItemPool>(TEXT("ItemPool"));

	MyComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Default"));
	SetRootComponent(MyComponent);

	// 기본 드랍 지속 시간
	SpawnInterval = 1.0f;
	MaxItemsToSpawn = 10;
	DropDuration = 2.0f; 
}


void AItemSpawner::BeginPlay()
{
    Super::BeginPlay();

    ItemPool->CreateItem( MaxItemsToSpawn );
}

void AItemSpawner::MoveItemAlongCurve( UObject* WorldContextObject , AActor* NewItem , FVector StartPoint , FVector ActorSpeed , float GravityScale )
{
	FVector VetorSeed = ActorSpeed;

	if (VetorSeed.IsNearlyZero())
		VetorSeed = UBezierMovementLibrary::VectorSeed( NewItem );

	UBezierMovementLibrary::MoveObjectAlongCurve( WorldContextObject , NewItem , StartPoint , VetorSeed , GravityScale );
}

void AItemSpawner::SetActive(AActor* Actor, bool IsActive)
{
	if(IsActive)
	{
		Actor->SetActorHiddenInGame( false );
		Actor->SetActorEnableCollision( true );
		Actor->SetActorTickEnabled(true);
	}
	else
	{
		Actor->SetActorHiddenInGame( true );
		Actor->SetActorEnableCollision( false );
		Actor->SetActorTickEnabled( false );
	}
}

UItemBase* AItemSpawner::GetItem( const FString& ID )
{
	return ItemPool->GetItem( ID );
}


//TArray<UItemBase*> AItemSpawner::GetItemAll()
//{
//	TArray<TObjectPtr<UItemBase>> ItemBases;
//
//	for(int32 i = 0; i < ItemIDArray.Num(); ++i)
//        ItemBases.Push(ItemPool->GetItem( ItemIDArray[i]));
//
//	return ItemBases;
//}

void AItemSpawner::CreateItem(const FString& ID, int32 ItemDropPercentage)
{
	UItemBase* ItemBase = ItemPool->GetItem(ID);
	ADroppedItem* DroppedItem = GetWorld()->SpawnActor<ADroppedItem>( FVector::ZeroVector , FRotator::ZeroRotator );
	DroppedItem->SetItemReference(ItemBase);
	DroppedItem->SetItemPercentage( ItemDropPercentage );
	DroppedItem->SetItemStaticMesh( ItemBase->GetAssetData().Mesh );

	SetActive(DroppedItem, false);

	DroppedItems.Push(DroppedItem);
}

void AItemSpawner::SpawnItem(AActor* SpawneItemActor)
{
	for(auto& elem : ItemSpawnerInfos)
	{
		const TObjectPtr<ADroppedItem>* FindItem = DroppedItems.FindByPredicate( [&]( const ADroppedItem* Item )
		{
			return Item->GetItemReference()->GetTextData().Name.ToString() == elem.Key;
		});

		if (elem.Value.DropPercentage > FMath::FRandRange( 0.0 , 100.f ))
		{
			const int32 ItemCount = FMath::RandRange( elem.Value.MinItemTodrop , elem.Value.MaxItemTodrop );

			FindItem->Get()->GetItemReference()->GetNumericData().bIsStackable
				? SpawnItemStackable( elem.Key , ItemCount, SpawneItemActor )
				: SpawnItemStackable( elem.Key , ItemCount, SpawneItemActor );
		}
	}
}

void AItemSpawner::SpawnItemStackable(const FString& ID, int32 ItemCont, AActor* SpawneItemActor )
{
	const int32 ItemCount = ItemCont;

	if(DroppedItems.Num() <= 0)
		CreateItem(ID, 100);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	ADroppedItem* DroppedItem = nullptr;

	// 몬스터 풀링 할 시 켜주세요.
	//TimerDelegate.BindLambda( [&]()
	//{
	//	SetActive( DroppedItem , true );
	//	MoveItemAlongCurve( this , DroppedItem , GetActorLocation() , FVector( 0.0 , 0.0 , 0.0 ) , 0.77f );
	//});

	for(int32 i = DroppedItems.Num() - 1; i >= 0; --i)
	{
		if (DroppedItems[i]->GetItemReference()->GetTextData().Name.ToString() == ID)
		{
			SetActive( DroppedItems[i] , true );
			DroppedItems[i]->SetMyItemSpawner( this );
			DroppedItems[i]->GetItemReference()->SetQuantity( ItemCount );
			DroppedItems[i]->SetActorLocation( GetActorLocation() );
			// 몬스터 풀링 시 켜주세요.
			//DroppedItem = DroppedItems[i];
			//GetWorld()->GetTimerManager().SetTimer( TimerHandle , TimerDelegate , 0.2f , false );
 			MoveItemAlongCurve( this , DroppedItems[i] , SpawneItemActor->GetActorLocation() , FVector(0.0 , 0.0 , 0.0) , 0.77f);
			//DroppedItems[i]->SetActorLocation( SpawneItemActor->GetActorLocation() );
			DroppedItems.RemoveAt( i );
			return;
		}
	}

}

void AItemSpawner::SpawnItemNoneStackable(const FString& ID, int32 ItemCont, AActor* SpawneItemActor )
{
	int32 ItemCount = ItemCont;

	if (DroppedItems.Num() <= 0)
		CreateItem( ID , 100 );

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	ADroppedItem* DroppedItem = nullptr;

	TimerDelegate.BindLambda( [&]()
	{
		SetActive( DroppedItem , true );
		MoveItemAlongCurve( this , DroppedItem , SpawneItemActor->GetActorLocation() , FVector( 0.0 , 0.0 , 0.0 ) , 0.77f );
	} );

	for (int32 i = DroppedItems.Num() - 1; i >= 0; --i)
	{
		if(!ItemCount)
			return;

		if (DroppedItems[i]->GetItemReference()->GetTextData().Name.ToString() == ID)
		{
			SetActive( DroppedItems[i] , true );
			DroppedItems[i]->SetMyItemSpawner( this );
			DroppedItems[i]->GetItemReference()->SetQuantity( 1 );
			DroppedItems[i]->SetActorLocation( GetActorLocation() );
			MoveItemAlongCurve( this , DroppedItems[i] , SpawneItemActor->GetActorLocation() , FVector( 0.0 , 0.0 , 0.0 ) , 0.77f );
			//DroppedItem = DroppedItems[i];
			//GetWorld()->GetTimerManager().SetTimer( TimerHandle , TimerDelegate , 0.2f , false );
			DroppedItems.RemoveAt( i );
			--ItemCount;
			++i;
		}
	}
}

void AItemSpawner::ReturnItem(ADroppedItem* DroppedItem)
{
	ItemPool->ReturnItem( DroppedItem->GetItemReference() );
	DroppedItems.Add( DroppedItem );
}

