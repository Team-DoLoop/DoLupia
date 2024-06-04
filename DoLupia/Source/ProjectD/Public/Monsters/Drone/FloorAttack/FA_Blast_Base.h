// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monsters/Drone/FloorAttack.h"
#include "FA_Blast_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API AFA_Blast_Base : public AFloorAttack
{
	GENERATED_BODY()

public:
	AFA_Blast_Base();

protected:
	virtual void Trigger() override;
	virtual void BeginPlay() override;


private:
	void PlayBlastSound();
	void SpawnBlast();

};
