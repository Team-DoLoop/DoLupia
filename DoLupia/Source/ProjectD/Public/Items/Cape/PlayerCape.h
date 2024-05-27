// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCape.generated.h"

UENUM(BlueprintType)
enum class EPlayerCapeColor : uint8
{
	RED UMETA(DisplayName = "Red"),
	YELLOW UMETA(DisplayName = "Yellow"),
	BLUE UMETA(DisplayName = "Blue"),
};


UCLASS()
class PROJECTD_API APlayerCape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerCape();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// <------------------------- AI ------------------------->
private:

public:
};
