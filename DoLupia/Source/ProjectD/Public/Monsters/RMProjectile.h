// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RMProjectile.generated.h"

UCLASS()
class PROJECTD_API ARMProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , 
		UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	UPROPERTY( EditAnywhere  )
	class USphereComponent* CollisionComponent;

	UPROPERTY( EditAnywhere )
	class UStaticMeshComponent* meshComp;

	//UPROPERTY( EditAnywhere )
	//class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	float speed = 3000;

	class AProjectDCharacter* player;

	UPROPERTY( EditAnywhere )
	class UParticleSystem* expVFX;
};
