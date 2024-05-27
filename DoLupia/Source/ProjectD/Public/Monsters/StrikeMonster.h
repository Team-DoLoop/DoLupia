// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monsters/Monster.h"
#include "StrikeMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AStrikeMonster : public AMonster
{
	GENERATED_BODY()



public:
	// Sets default values for this character's properties
	AStrikeMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* SwordCollision;

	virtual void OnMyCompBeginOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor ,
	                                   UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult ) override;

	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* Weapon;

	virtual void AttackState() override;


};