
#include "Spawner/ItemSpawner.h"

#include "Pooling/ItemPool.h"
#include "Library/BezierMovementLibrary.h"

AItemSpawner::AItemSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

    ItemPool = CreateDefaultSubobject<UItemPool>(TEXT("ItemPool"));

	// 기본 드랍 지속 시간
	SpawnInterval = 1.0f;
	MaxItemsToSpawn = 10;
	DropDuration = 2.0f; 
}

void AItemSpawner::MoveItemAlongCurve( UObject* WorldContextObject, AActor* NewItem, FVector StartPoint, FVector ActorSpeed, float GravityScale )
{
    UBezierMovementLibrary::MoveObjectAlongCurve( WorldContextObject , NewItem , StartPoint, ActorSpeed, GravityScale );
}

TArray<UItemBase*> AItemSpawner::SpawnItemAll()
{
	TArray<TObjectPtr<UItemBase>> ItemBases;

	for(int32 i = 0; i < ItemIDArray.Num(); ++i)
        ItemBases.Push(ItemPool->GetItem( ItemIDArray[i]));

	return ItemBases;
}

void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();

	ItemPool->CreateItem( MaxItemsToSpawn );
}

UItemBase* AItemSpawner::SpawnItem()
{
    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    // 위치와 회전 값을 XOR 연산하여 고유한 시드 값 생성
    // 나중에 확률 추가하려면 따로 구현 해야함.
    //uint32 Seed = Location.X;
    //Seed = Seed ^ (uint32)Location.Y;
    //Seed = Seed ^ (uint32)Location.Z;
    //Seed = Seed ^ (uint32)Rotation.Pitch;
    //Seed = Seed ^ (uint32)Rotation.Yaw;
    //Seed = Seed ^ (uint32)Rotation.Roll;

    //FRandomStream RandomStream( Seed );

    return nullptr;
	//return ItemPool->GetItem( ItemIDArray[RandomStream.RandRange( 0 , ItemIDArray.Num() )] );
}
