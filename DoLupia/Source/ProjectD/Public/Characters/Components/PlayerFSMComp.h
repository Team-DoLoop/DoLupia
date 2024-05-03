// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PlayerStateBase.h"
#include "Components/ActorComponent.h"
#include "PlayerFSMComp.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTemplatePlayerFSM, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerFSMComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFSMComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// <--------------------- Player --------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class UCharacterMovementComponent* PlayerMovement;

public:


	// <--------------------- Player Controller --------------------->
	
private:
	friend class AProjectDPlayerController;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;


public:

	
	// <--------------------- State --------------------->
private:
	UPROPERTY()
	EPlayerState CurrentState = EPlayerState::IDLE;


public:
	void ChangePlayerState(EPlayerState _state);
	
};
