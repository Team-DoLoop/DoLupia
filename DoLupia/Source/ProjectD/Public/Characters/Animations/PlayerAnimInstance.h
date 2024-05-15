// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/PlayerStateBase.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */

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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerState State;

	void PlayMontage(UAnimMontage* _Montage);

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
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* attackMontage;

	void PlayerAttackAnimation(int32 SkillIndex);
	
	UFUNCTION()
	void AnimNotify_AttackJudgmentStart();

	UFUNCTION()
	void AnimNotify_AttackJudgmentEnd();



};
