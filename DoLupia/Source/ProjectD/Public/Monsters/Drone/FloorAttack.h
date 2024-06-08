// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorAttack.generated.h"

#define DEBUG_MY_FLOORATTAK

class UNiagaraSystem;
class USoundBase;
class USphereComponent;
class UDecalComponent;
class UMaterialInterface;

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

	UFUNCTION(BlueprintCallable)
	void IgnoreActorsClear();

	bool ActorSameType( AActor* OtherActor );

	virtual void Trigger();

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY( EditDefaultsOnly , Category = "Weapon Properties" )
	USoundWave* SpawnSound;

	UPROPERTY( EditDefaultsOnly , Category = "Weapon Properties" )
	UNiagaraSystem* SpawnEffect;

	UPROPERTY( EditDefaultsOnly , BlueprintReadWrite, Category = "Weapon Properties" )
	USphereComponent* AttackSphere;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Components" )
	UDecalComponent* DecalComp;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Effects" )
	UMaterialInterface* DecalMaterial;

	UPROPERTY()
	TSet<AActor*> IgnoerActors;

	UPROPERTY(EditDefaultsOnly)
	float AttackDamage = 20;

	UPROPERTY(EditDefaultsOnly)
	float AttackRadius = 200.f;

	UPROPERTY(EditDefaultsOnly)
	bool ChaseTarget;

	

private:
	void SpawnAOESphere();

};
