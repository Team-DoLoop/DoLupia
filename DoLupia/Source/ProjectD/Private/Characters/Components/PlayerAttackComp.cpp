// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "EnhancedInputComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "Characters/Skill/PlayerSkillCastingHitDown.h"
#include "Characters/Skill/PlayerSkillSpell.h"
#include "Characters/Skill/PlayerSkillSwing.h"
#include "Characters/Skill/PlayerSkillUlt.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPlayerAttackComp::UPlayerAttackComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerAttackComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = Cast<AProjectDCharacter>(GetOwner());
	if(!Player) return;
	
	PlayerController = Cast<AProjectDPlayerController>(Player->GetController());
	PlayerFSMComp = Player->GetPlayerFSMComp();
	PlayerAnim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
	
	PlayerSkills.Add(NewObject<UPlayerSkillSwing>());
	PlayerSkills.Add(NewObject<UPlayerSkillSpell>());
	PlayerSkills.Add(NewObject<UPlayerSkillCastingHitDown>());
	PlayerSkills.Add(NewObject<UPlayerSkillUlt>());
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerAttackComp::TurnPlayer()
{
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if(bHitSuccessful)
	{
		FVector AttackVec = Hit.ImpactPoint - Player->GetActorLocation();
		FRotator TargetRot = UKismetMathLibrary::MakeRotFromXZ( AttackVec , Player->GetActorUpVector() );
		FRotator PlayerRot = Player->GetActorRotation();
		FRotator TempRot = FRotator(PlayerRot.Pitch, TargetRot.Yaw, PlayerRot.Roll);
		Player->SetActorRotation( TempRot);
	}
}

void UPlayerAttackComp::Attack()
{
	if(!PlayerFSMComp) return;
	if(!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;
	
	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	TurnPlayer();
	
	if(!PlayerAnim) return;
	PlayerAnim->PlayerAttackAnimation(0);
}

void UPlayerAttackComp::AttackEnd()
{
	if(!PlayerFSMComp) return;
	PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);
}


void UPlayerAttackComp::PlayerExecuteSkill(int32 SkillIndex)
{
	if(!PlayerFSMComp) return;
	if(!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;

	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	TurnPlayer();
	
	// 스킬 애니메이션 실행
	PlayerAnim->PlayerAttackAnimation(SkillIndex + 1);
	
	// 스킬 기능 실행
	if(SkillIndex >= 0 && SkillIndex < PlayerSkills.Num())
	{
		if(!PlayerSkills[SkillIndex]) return;
		PlayerSkills[SkillIndex]->ExecuteSkill();
	}
}

