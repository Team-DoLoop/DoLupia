// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "ProjectDPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AProjectDPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// To add mapping context
	virtual void BeginPlay();
	
public:
	AProjectDPlayerController();

	// <---------------------- Not Use ---------------------->
	/*
private:

protected:
	void OnTouchTriggered();
	void OnTouchReleased();
	
public:


	// Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;
	
*/


	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* ControlledCharacter;
	
protected:

public:

	
	
	// <---------------------- Input ---------------------->
private:

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	// uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;


	
	// <---------------------- Move ---------------------->
private:

protected:
	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	
	void Evasion();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EvasionAction;


	
	// <---------------------- UI ---------------------->
private:
	void ToggleMenu();

public:
	/* Toggle Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleAction;
	

	
	// <---------------------- Interaction ---------------------->
private:
	void BeginInteract();
	void EndInteract();

public:
	/* Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;



	// <---------------------- Attack ---------------------->
private:
	void Aim();
	void StopAiming();

protected:
	void Attack();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimingAction;


};


