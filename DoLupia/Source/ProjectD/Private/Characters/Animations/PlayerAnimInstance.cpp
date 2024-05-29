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


class AMonster;

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
/*
void UPlayerAnimInstance::PlayerAttackAnimation(int32 SkillIndex)
{
	if(!attackMontage) return;

	// 검 소지 중인지 아닌지 나눠주기
	// 검을 들고 있다면?
	PlayMontage(attackMontage);
	Montage_JumpToSection(SkillAnimationName[SkillIndex],attackMontage);
	
	
	// 안들고 있다면?
}
*/

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
	
	TArray<AActor*> TargetActors;
	FVector AttackRange = Player->GetAttackComp()->GetAttackRange();
	FVector PlayerLoc = Player->GetActorLocation();
	FVector BoxPos = FVector(AttackRange.X + PlayerLoc.X, AttackRange.Y + PlayerLoc.Y, PlayerLoc.Z);

	int32 AttackDamage = Player->GetAttackComp()->GetAttackDamage();
	
	DrawDebugBox(GetWorld(), BoxPos, AttackRange, FColor::Red, false, 3.0f);
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), BoxPos, AttackRange,
		TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(),
		TargetActors);
	for(auto TargetActor : TargetActors)
	{
		if (AMonster* Monster = Cast<AMonster>(TargetActor))
		{
			Monster->OnMyTakeDamage(AttackDamage);
			UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster"), *Monster->GetName());
		}
	}
}

void UPlayerAnimInstance::AnimNotify_AttackJudgmentEnd()
{
	// 공격 판정 끝
	UE_LOG(LogTemp, Log, TEXT("Attack Judgment End"));

	//ASwordBase* Sword = Gadget->GetSword();
	//if(!Sword) return;
	//Sword->CollisionOff();
}