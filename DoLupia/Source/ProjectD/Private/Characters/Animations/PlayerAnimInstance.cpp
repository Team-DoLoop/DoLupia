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
	
	if(!Player) return;
	Gadget = Player->GetGadgetComp();
	
	SkillAnimationName = {"Default", "SkillSwing", "SkillSpell", "SkillCastingHitDown", "SkillUlt"};
	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!Player) return;

	State =  Player->GetPlayerFSMComp()->GetCurrentState();
	WeaponState = Player->GetPlayerFSMComp()->GetCurrentWeaponState();
	Velocity = Player->GetVelocity();
	Speed = UKismetMathLibrary::VSizeXY(Velocity);
}

void UPlayerAnimInstance::PlayMontage(UAnimMontage* _Montage)
{
	if(!_Montage) return;

	Montage_Play(_Montage);
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("Player Animation Montage End"));
	if(!Player) return;
	
	// End Attack Montage
	if(Montage->GetFName() == attackMontage->GetFName())
		Player->GetAttackComp()->AttackEnd();
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
	PlayMontage(evasionMontage);
}

void UPlayerAnimInstance::PlayerDieAnimation()
{
	if(!dieMontage) return;
	PlayMontage(dieMontage);
}


// <---------------------- Attack ---------------------->

void UPlayerAnimInstance::PlayerAttackAnimation(int32 SkillIndex)
{
	if(!attackMontage) return;

	// 검 소지 중인지 아닌지 나눠주기
	// 검을 들고 있다면?
	PlayMontage(attackMontage);
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