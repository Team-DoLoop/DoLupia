// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestItem.generated.h"

UCLASS()
class PROJECTD_API ATestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestItem();

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

protected:

	UPROPERTY( VisibleAnywhere )
	class USphereComponent* MyCollisionSphere;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
