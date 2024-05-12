// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monsters/Monster.h"
#include "RangedMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API ARangedMonster : public AMonster
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ARangedMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* Weapon;

	//virtual void MoveState() override;
	virtual void AttackState() override;

	float attackDelayTime = 6;

	UPROPERTY( EditAnywhere )
	float DelayTime = 3;

	//Looping 여부
	UPROPERTY( EditAnywhere )
	bool bIsLoop = true;

	//원거리 공격
	void RangedAttack();

	float currentTimeRM = 0;

	
};
