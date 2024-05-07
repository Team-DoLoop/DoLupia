// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/PlayerAnimInstance.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Kismet/KismetMathLibrary.h"


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<AProjectDCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!Player) return;

	State =  Player->GetPlayerFSMComp()->GetCurrentState();
	Velocity = Player->GetVelocity();
	Speed = UKismetMathLibrary::VSizeXY(Velocity);
	
}


// <---------------------- Move ---------------------->
void UPlayerAnimInstance::AnimNotify_PlayerEvasionEnd()
{
	if(!Player) return;
	Player->GetPlayerMoveComp()->EvasionEnd();
}

void UPlayerAnimInstance::PlayerEvasionAnimation()
{
	if(!evasionMontage) return;
	Montage_Play(evasionMontage);
}


// <---------------------- Attack ---------------------->
void UPlayerAnimInstance::AnimNotify_AttackJudgmentStart()
{
	// 공격 판정 시작
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment Start"));
}

void UPlayerAnimInstance::AnimNotify_AttackJudgmentEnd()
{
	// 공격 판정 끝
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment End"));
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	if(!Player) return;
	Player->GetAttackComp()->AttackEnd();
}

void UPlayerAnimInstance::PlayerAttackAnimation()
{
	if(!attackMontage) return;
	Montage_Play(attackMontage);
}
