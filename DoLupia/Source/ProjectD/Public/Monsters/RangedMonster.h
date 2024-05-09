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

	virtual void AttackState() override;
};
