// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossDroneLaser.generated.h"

class ABossDrone;
class UNiagaraSystem;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class PROJECTD_API ABossDroneLaser : public AActor
{
	GENERATED_BODY()

public:	
	ABossDroneLaser();

	void MoveLaser(float DeltaTime);

	void Initialize(ABossDrone* MyDrone);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// 레이저 발사 초기화 함수
	void Initialize(const FVector& InDirection , float InSpeed );

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DumpSceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY()
	ABossDrone* Drone;

	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent , AActor* OtherActor , 
		UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit );

	UPROPERTY(EditDefaultsOnly)
	float Speed;

	FVector CurrentLocation;
	FVector SpeedLocation;

	FVector Direction;
};
