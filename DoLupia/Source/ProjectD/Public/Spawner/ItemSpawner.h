// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class UItemPool;
class UItemBase;

UCLASS()
class PROJECTD_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemSpawner();

	static void MoveItemAlongCurve( UObject* WorldContextObject, AActor* NewItem, FVector StartPoint, FVector ActorSpeed, float GravityScale );

	TArray<UItemBase*> SpawnItemAll();

public:
	FORCEINLINE void AddItemID(const FString& ItemID ){ ItemIDArray.Push(ItemID); }

protected:
	virtual void BeginPlay() override;


protected:
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

private:
	UItemBase* SpawnItem();

};
