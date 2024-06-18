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
	FORCEINLINE EPlayerState GetCurrentState() const { return CurrentState; }
	void CheckState(EPlayerState _state);
	
	// UFUNCTION(BlueprintCallable)
	void ChangePlayerState(EPlayerState _state);

	// UFUNCTION(BlueprintCallable)
	bool CanChangeState(EPlayerState _changeState);


	// <--------------------- Weapon State --------------------->
private:
	UPROPERTY()
	EPlayerWeaponState CurrentWeaponState = EPlayerWeaponState::UNARMED;

public:
	FORCEINLINE EPlayerWeaponState GetCurrentWeaponState() const { return CurrentWeaponState; }
	void ChangePlayerWeaponState(EPlayerWeaponState _weaponState);

	
	// <--------------------- Shield State --------------------->
private:
	UPROPERTY()
	EPlayerShieldState CurrentShieldState = EPlayerShieldState::NONE;

public:
	FORCEINLINE EPlayerShieldState GetCurrentShieldState() const { return CurrentShieldState; }
	void ChangePlayerShieldState(EPlayerShieldState _shieldState);


	// <--------------------- IDLE --------------------->
private:

public:
	bool CanIdleState(EPlayerState _CurrentState);

	
	// <--------------------- Move --------------------->
private:

public:
	void TickMove();
	bool CanMoveState(EPlayerState _CurrentState);

	
	// <--------------------- Evasion --------------------->
private:

public:
	bool CanEvasionState(EPlayerState _CurrentState);

	
	// <--------------------- Attack --------------------->
private:

public:
	bool CanAttackState(EPlayerState _CurrentState, EPlayerWeaponState _CurrentWeaponState);
	bool CanAttackWithState(EPlayerState _CurrentState);

	
	// <--------------------- Damage --------------------->
private:

public:
	bool CanLyingState(EPlayerState _CurrentState);
	bool CanDamageState(EPlayerState _CurrentState);
	bool CanGrabState(EPlayerState _CurrentState);


	// <--------------------- TalkNPC --------------------->
private:

public:
	bool CanTalkNPCState(EPlayerState _CurrentState);
	

	// <--------------------- Die --------------------->
private:

public:
	bool CanDieState(EPlayerState _CurrentState);
};
