// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Animations/PlayerAnimInstance.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Items/Sword/SwordBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Monsters/Monster.h"


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

void UPlayerAnimInstance::StopMontage()
{
	if(AttackMontage && Montage_IsPlaying(AttackMontage)) Montage_Stop(0.5f, AttackMontage);
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Log, TEXT("Player Animation Montage End"));
	if(!Player) return;

	FName MontageName = Montage->GetFName();
	// End Attack Montage
	if(AttackMontage && MontageName == AttackMontage->GetFName())
		Player->GetAttackComp()->CompleteSkill();
	else if(LyingMontage && MontageName == LyingMontage->GetName())
		Player->LyingEnd();
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

void UPlayerAnimInstance::PlayAttackAnimation(UAnimMontage* _Montage)
{
	if(!_Montage) return;
	UE_LOG(LogTemp, Log, TEXT("PlayAttackAnimation : %s"), *_Montage->GetFName().ToString());
	AttackMontage = _Montage;
	PlayMontage(_Montage);
}

void UPlayerAnimInstance::PlayerLyingAnimation()
{
	if(!LyingMontage) return;

	PlayMontage(LyingMontage);
}


void UPlayerAnimInstance::AnimNotify_AttackJudgmentStart()
{
	// 공격 판정 시작
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment Start"));
	if(!Player || !Gadget) return;

	//ASwordBase* Sword = Gadget->GetSword();
	//if(!Sword) return;
	//Sword->CollisionOn();
	
	Player->GetAttackComp()->MeleeSkillAttackJudgementStart();
}

void UPlayerAnimInstance::AnimNotify_AttackJudgmentEnd()
{
	// 공격 판정 끝
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment End"));
	Player->GetAttackComp()->MeleeSkillAttackJudgementEnd();
	
	//ASwordBase* Sword = Gadget->GetSword();
	//if(!Sword) return;
	//Sword->CollisionOff();
}

void UPlayerAnimInstance::AnimNotify_AttackRangedStart()
{
	Player->GetAttackComp()->RangedSkillAttackJudgementStart();
}

void UPlayerAnimInstance::AnimNotify_AttackRangedEnd()
{
	Player->GetAttackComp()->RangedSkillAttackJudgmentEnd();
}

void UPlayerAnimInstance::AnimNotify_AttackShieldStart()
{
	Player->GetAttackComp()->ShieldSkillStart();
}

void UPlayerAnimInstance::AnimNotify_AttackUltStart()
{
	Player->GetAttackComp()->ExecuteUltSkill();
}

void UPlayerAnimInstance::AnimNotify_AttackWith()
{
	Player->GetAttackComp()->CompleteSkill();
}

void UPlayerAnimInstance::AnimNotify_AttackWaterBlade()
{
	Player->GetAttackComp()->PlayerWaterBladeSkill();
}


FName UPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	if(FMath::IsWithinInclusive<int32>(Section, 1, 4))
	{
		return FName(*FString::Printf(TEXT("Combo%d"), Section));
	}
	return "";
}

void UPlayerAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if(Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp,Log,TEXT("Montage Play : %d"), NewSection);
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
	}
}


void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_NextChargingCheck()
{
	Player->GetAttackComp()->NextChargingCheck();
}
