// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnMonsterDamage.generated.h"

UCLASS()
class PROJECTD_API ASpawnMonsterDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnMonsterDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly )
	class UWidgetComponent* damageUI;

	UPROPERTY()
	class UMonsterDamageWidget* monsterDamageWidget;

	void DestroyActor();
};
