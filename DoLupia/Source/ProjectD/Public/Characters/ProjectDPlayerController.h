// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "ProjectDPlayerController.generated.h"

/** Forward declaration to improve compiling times */
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UWidgetQuestLog;

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

	// <---------------------- Test ---------------------->
private:
	int32 TestCount = 0;

protected:
	void TestAnyFunction();
	void GetInputModeString() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TestAction;
	

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
	bool IsHoverd();
	void UseQuickSlot(int32 QuickSlotNumber);

private:
	/* Toggle Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleAction;
	
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot1Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot2Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot3Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot4Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot5Action;
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot6Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot7Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot8Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot9Action;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuickSlot0Action;

	
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
	// void Attack();
	void QuitSkill(int32 SkillIndex);
	void ExecuteSkill(int32 SkillIndex);
	void ChargingSkill(int32 SkillIndex);
	void ChargingEndSkill(int32 SkillIndex);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimingAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwingSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpellSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CastingHitDownSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UltSkillAction;



	// <---------------------- QuestUI ---------------------->

public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* QuestTabAction;
	
	UPROPERTY( EditAnywhere )
	TSubclassOf<UWidgetQuestLog> QuestLog_Widget;

private:
	void QuestLogMenu();


	
	// <---------------------- Tutorial ---------------------->
public:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , Category = Input , meta = (AllowPrivateAccess = "true") )
	UInputAction* ToToAction;

private:
	void StartToToStory();

};


