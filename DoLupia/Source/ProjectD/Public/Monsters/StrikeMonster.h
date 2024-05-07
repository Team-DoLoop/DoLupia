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

	UPROPERTY( VisibleAnywhere )
	UStaticMeshComponent* Weapon;

	//virtual void AttackState() override;
};