// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OctopusBackpackComponent.h"
#include "OctopusBackpackActor.h"
#include "AI/BTTask_Attack.h"
#include "Components/ActorComponent.h"
#include "BossMonster.generated.h"

DECLARE_MULTICAST_DELEGATE( FOnAttackEndDelegate );

UCLASS()
class PROJECTD_API ABossMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ABossMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY( EditAnywhere , Category = "Components" )
	//UOctopusBackpackComponent* OctopusBackpackComponent;
	//
	//UPROPERTY( EditAnywhere,BlueprintReadWrite , Category = "Components" )
	//UChildActorComponent* ChildActorComponent;

	UFUNCTION()
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	float currentTime = 0;
};
