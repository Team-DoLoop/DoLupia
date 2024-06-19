// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/PlayerStateBase.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);

UCLASS()
class PROJECTD_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class UGadgetComponent* Gadget;

	UPROPERTY()
	class UPlayerAttackComp* PlayerAttack;

	UPROPERTY()
	class UPlayerFSMComp* PlayerFSM;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerWeaponState WeaponState;

	void PlayMontage(UAnimMontage* _Montage);
	void StopMontage();

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool bInterrupted);
	

	
	// <---------------------- Move ---------------------->
private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* evasionMontage;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* dieMontage;

	UFUNCTION()
	void AnimNotify_PlayerEvasionEnd();
	
	void PlayerEvasionAnimation();
	void PlayerDieAnimation();

	
	// <---------------------- Attack ---------------------->
private:
	TArray<FName> SkillAnimationName;

public:
	UPROPERTY()
	class UAnimMontage* AttackMontage;
	
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* LyingMontage;

	void PlayAttackAnimation(class UAnimMontage* _Montage);


		
	// <---------------------- Hit ---------------------->
public:
	void PlayerLyingAnimation();

	UFUNCTION()
	void AnimNotify_GrabEnd();

	

	// <---------------------- Skill ---------------------->
	UFUNCTION()
	void AnimNotify_AttackJudgmentStart();

	UFUNCTION()
	void AnimNotify_AttackJudgmentEnd();

	UFUNCTION()
	void AnimNotify_AttackRangedStart();

	UFUNCTION()
	void AnimNotify_AttackRangedEnd();

	UFUNCTION()
	void AnimNotify_AttackShieldStart();

	

	UFUNCTION()
	void AnimNotify_AttackUltStart();

	UFUNCTION()
	void AnimNotify_AttackWith();

	UFUNCTION()
	void AnimNotify_AttackWaterBlade();

	
	// <---------------------- Combo ---------------------->
private:
	FName GetAttackMontageSectionName(int32 Section);
	
public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	void JumpToAttackMontageSection(int32 NewSection);

	UFUNCTION()
	void AnimNotify_NextAttackCheck();


	// <---------------------- Charging ---------------------->
public:
	UFUNCTION()
	void AnimNotify_NextChargingCheck();
	

private:

};
