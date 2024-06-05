﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerBaseActor.generated.h"

class UBoxComponent;
class APlayerGameMode;
class UNiagaraComponent;

UCLASS()
class PROJECTD_API ATriggerBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	UBoxComponent* triggerComp;

	UPROPERTY()
	APlayerGameMode* gm;

	/* ------------------- Open Level ------------------- */
public:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "Change Level" )
	FName LvName;

	void CallLevel( FName Lvname);

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UNiagaraComponent* locationVFX;

	

};
