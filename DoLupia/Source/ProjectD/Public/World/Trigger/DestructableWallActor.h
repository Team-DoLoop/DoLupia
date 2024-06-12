// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructableWallActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class PROJECTD_API ADestructableWallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructableWallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UGeometryCollectionComponent* DestructableWallComp;

	void ExplosionWalls();

};
