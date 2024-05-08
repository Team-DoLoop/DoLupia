// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Sword/LongSword.h"

ALongSword::ALongSword()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALongSword::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALongSword::BeginPlay()
{
	Super::BeginPlay();
}
