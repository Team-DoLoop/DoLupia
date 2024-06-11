// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class UItemPool;
class UItemBase;
class ADroppedItem;

USTRUCT( BlueprintType )
struct FItemSpawnerInfo
{
	GENERATED_USTRUCT_BODY()

	// 아이템 이름
	UPROPERTY( EditAnywhere , Category = "Spawner Infomation" )
	FString ItemName;

	// 아이템 드랍 확률 
	UPROPERTY( EditAnywhere , Category = "Spawner Infomation" )
	float DropPercentage;

	/*
		Min -> 1, Max -> 5
		1개 이상 5개 미만으로 드랍개수가 정해짐
	*/

	UPROPERTY( EditAnywhere , Category = "Spawner Infomation" )
	int32 MinItemTodrop;

	UPROPERTY( EditAnywhere , Category = "Spawner Infomation" )
	int32 MaxItemTodrop;

};

UCLASS()
class PROJECTD_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawner();

	static void MoveItemAlongCurve( UObject* WorldContextObject, AActor* NewItem, FVector StartPoint, float Time,
		FVector ActorSpeed = FVector(0.0, 0.0, 0.0) , float GravityScale = 0.5f);

	UItemBase* GetItem( const FString& ID );
	//TArray<UItemBase*> GetItemAll();

	void CreateItem( const FString& ID, int32 ItemDropPercentage );
	void ReturnItem( ADroppedItem* DroppedItem );
	void SpawnItem( AActor* SpawneItemActor );

	void SetActive( AActor* Actor , bool IsActive );

public:
	//FORCEINLINE void AddItemID(const FString& ItemID ) { ItemIDArray.Push(ItemID); }
	FORCEINLINE void EditItemSpawnerInfo( FItemSpawnerInfo NewItemSpawnerInfo )
	{ ItemSpawnerInfos.Emplace( NewItemSpawnerInfo.ItemName, NewItemSpawnerInfo ); }

protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* MyComponent;

	/* Pooling */
	UPROPERTY()
	TObjectPtr<UItemPool> ItemPool;

	/* Item Bezier */

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	float SpawnInterval;

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	int32 MaxItemsToSpawn;

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	FVector StartPoint;

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	FVector ControlPoint;

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	FVector EndPoint;

	UPROPERTY( EditAnywhere , Category = "Spawning" )
	float DropDuration;

	UPROPERTY(EditDefaultsOnly)
	TArray<FString> ItemIDArray;

	UPROPERTY()
	TArray<TObjectPtr<ADroppedItem>> DroppedItems;

	UPROPERTY(VisibleAnywhere)
	TMap<FString, FItemSpawnerInfo> ItemSpawnerInfos;

private:
	void SpawnItemStackable( const FString& ID, int32 ItemCont, AActor* SpawneItemActor );
	void SpawnItemNoneStackable( const FString& ID, int32 ItemCont, AActor* SpawneItemActor );

};
