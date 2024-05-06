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

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeInitializeAnimation() override;


	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerState State;
	

	
	// <---------------------- Move ---------------------->
private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;


	
	// <---------------------- Attack ---------------------->
private:

public:
	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* attackMontage;
	
	void PlayerAttackAnimation();

};
