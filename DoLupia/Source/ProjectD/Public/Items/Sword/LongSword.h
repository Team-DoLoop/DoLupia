// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Sword/SwordBase.h"
#include "LongSword.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API ALongSword : public ASwordBase
{
	GENERATED_BODY()

public:
	ALongSword();
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;


};
