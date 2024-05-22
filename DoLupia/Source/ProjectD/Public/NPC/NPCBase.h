// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

UCLASS()
class PROJECTD_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

	// Function to call delegate
	UFUNCTION()
	void CallNPCMessageDelegate( FString Message );

	UPROPERTY()
	class UAIConnectionLibrary* AIlib;


private:

	UPROPERTY()
	class APlayerGameMode* gm;



	FString NPCConversation;

};
