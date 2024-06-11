// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroppedItem.generated.h"

class UDataTable;
class AItemSpawner;
class UItemBase;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTD_API ADroppedItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroppedItem();

	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference;}
	FORCEINLINE int32 GetItemPercentage() const { return ItemPercentage; }

	FORCEINLINE void SetItemReference( UItemBase* NewItemReference ) { ItemReference = NewItemReference;}
	FORCEINLINE void SetItemPercentage(int32 NewItemPercentage) { ItemPercentage = NewItemPercentage;}

	FORCEINLINE void SetMyItemSpawner( AItemSpawner* NewMyItemSpawner ) { MyItemSpawner = NewMyItemSpawner; }
	FORCEINLINE void SetStartLocation( FVector NewStartLocation ) { StartLocation = NewStartLocation; }

	void SetItemStaticMesh(UStaticMesh* StaticMesh);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnTouchesGroundBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
		UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Drop | Components")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Drop | Components" )
	UStaticMeshComponent* ItemMesh;

private:
	void PerformBoxTrace(float DeltaTime);


private:
	UPROPERTY()
	UItemBase* ItemReference;

	UPROPERTY()
	AItemSpawner* MyItemSpawner;

	uint32 ItemPercentage;

	FRotator OriRotator;
	FRotator SpinRotator;

	FVector StartLocation;

	FVector ActorSpeed;

	FVector MeshScale;

	float Time;

};
