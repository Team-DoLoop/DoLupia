// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "EnhancedInputComponent.h"
#include "Characters/PlayerStat.h"
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
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"

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
	PlayerStat = Cast<APlayerStat>(Player->GetPlayerState());

	// PlayerSkill
	PlayerSkills.Add(NewObject<UPlayerSkillSwing>());
	PlayerSkills.Add(NewObject<UPlayerSkillSpell>());
	PlayerSkills.Add(NewObject<UPlayerSkillCastingHitDown>());
	PlayerSkills.Add(NewObject<UPlayerSkillUlt>());

	// PlayerMP
	if(PlayerStat)
	{
		PlayerMaxMP = PlayerStat->GetMaxMP();
	}
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerAttackComp::Attack()
{
	if(!Player || !PlayerFSMComp) return;
	if(!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;
	
	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	Player->TurnPlayer();
	
	if(!PlayerAnim) return;
	PlayerAnim->PlayerAttackAnimation(0);
}

void UPlayerAttackComp::AttackEnd()
{
	if(!PlayerFSMComp) return;
	PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);

	if(!Player->GetPlayerDefaultsWidget()->GetMainQuickSlot()->IsDraggingWidget())
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		PlayerController->SetInputMode( InputMode );
	}

	
}


void UPlayerAttackComp::PlayerExecuteSkill(int32 SkillIndex)
{
	if(!Player || !PlayerFSMComp || !PlayerStat) return;
	if(!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;

	// 스킬 기능 실행
	if(SkillIndex >= 0 && SkillIndex < PlayerSkills.Num())
	{
		if(!PlayerSkills[SkillIndex]) return;
		
		// MP가 있다면
		int32 CurrentMP = PlayerStat->GetMP() - PlayerSkills[SkillIndex]->GetSkillCost();
		if(CurrentMP >= 0)
		{
			PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);
			
			Player->TurnPlayer();
			
			// 스킬 애니메이션 실행
			PlayerAnim->PlayerAttackAnimation(SkillIndex + 1);

			// 스킬 실행
			PlayerSkills[SkillIndex]->ExecuteSkill();

			// MP 소모
			PlayerStat->SetMP(CurrentMP);
			Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP, PlayerMaxMP);
		}
	}
}

