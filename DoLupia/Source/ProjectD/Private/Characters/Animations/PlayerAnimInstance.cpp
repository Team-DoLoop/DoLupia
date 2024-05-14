// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/PlayerAnimInstance.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Items/Sword/SwordBase.h"
#include "Kismet/KismetMathLibrary.h"


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<AProjectDCharacter>(TryGetPawnOwner());
	SkillAnimationName = {"Default", "SkillSwing", "SkillSpell", "SkillCastingHitDown", "SkillUlt"};
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!Player) return;

	State =  Player->GetPlayerFSMComp()->GetCurrentState();
	Velocity = Player->GetVelocity();
	Speed = UKismetMathLibrary::VSizeXY(Velocity);
	Gadget = Player->GetGadgetComp();
	
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

void UPlayerAnimInstance::PlayerDieAnimation()
{
	if(!dieMontage) return;
	Montage_Play(dieMontage);
}


// <---------------------- Attack ---------------------->

void UPlayerAnimInstance::PlayerAttackAnimation(int32 SkillIndex)
{
	if(!attackMontage) return;

	// 검 소지 중인지 아닌지 나눠주기
	// 검을 들고 있다면?
	Montage_Play(attackMontage);
	Montage_JumpToSection(SkillAnimationName[SkillIndex],attackMontage);
	
	
	// 안들고 있다면?
}

void UPlayerAnimInstance::AnimNotify_AttackJudgmentStart()
{
	// 공격 판정 시작
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment Start"));
	if(!Player || !Gadget) return;

	ASwordBase* Sword = Gadget->GetSword();
	if(!Sword) return;
	Sword->CollisionOn();
}

void UPlayerAnimInstance::AnimNotify_AttackJudgmentEnd()
{
	// 공격 판정 끝
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment End"));

	ASwordBase* Sword = Gadget->GetSword();
	if(!Sword) return;
	Sword->CollisionOff();
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	if(!Player) return;
	Player->GetAttackComp()->AttackEnd();
}