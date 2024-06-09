﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monsters/Drone/FloorAttack/FA_Blast_Base.h"
#include "FA_Blast_Fire.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AFA_Blast_Fire : public AFA_Blast_Base
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick( float DeltaTime ) override;

private:
	virtual void Trigger() override;

private:
	UFUNCTION()
	void CollisionEnd();

	UFUNCTION()
	void CollisionStart();
	
};
