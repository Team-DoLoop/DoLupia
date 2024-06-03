// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorAttack.generated.h"

class USoundBase;
class USphereComponent;

UCLASS()
class PROJECTD_API AFloorAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	AFloorAttack();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
		UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	bool ActorSameType( AActor* OtherActor );

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY( EditDefaultsOnly , Category = "Weapon Properties" )
	USoundBase* SpawnSound;

	UPROPERTY( EditDefaultsOnly , Category = "Weapon Properties" )
	USphereComponent* AttackSphere;

	TArray<AActor*> IgnoerActors;

	UPROPERTY(EditDefaultsOnly)
	float AttackDamage = 20;

};
