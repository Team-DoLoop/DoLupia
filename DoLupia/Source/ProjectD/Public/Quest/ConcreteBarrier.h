// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConcreteBarrier.generated.h"

class UBoxComponent;
class UMeshComponent;

UCLASS()
class PROJECTD_API AConcreteBarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConcreteBarrier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UMeshComponent* MeshComponent;

	UFUNCTION()
	void BarrierRelease( bool onoff );
};
