// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "EnhancedInputComponent.h"
#include "ProjectDGameInstance.h"
#include "Characters/PlayerStat.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "Characters/Skill/PlayerSkillMelee.h"
#include "Characters/Skill/PlayerSkillSwap.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"
#include "UserInterface/Skill/PlayerSkillSlotWidget.h"
#include "UserInterface/Skill/PlayerSkillWidget.h"

// Sets default values for this component's properties
UPlayerAttackComp::UPlayerAttackComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UPlayerAttackComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Player = Cast<AProjectDCharacter>(GetOwner());
	if (!Player) return;

	PlayerController = Cast<AProjectDPlayerController>(Player->GetController());
	PlayerFSMComp = Player->GetPlayerFSMComp();
	PlayerAnim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
	PlayerStat = Cast<APlayerStat>(Player->GetPlayerState());

	/*
	// PlayerSkill
	PlayerSkills.Add(NewObject<UPlayerSkillMelee>());
	PlayerSkills.Add(NewObject<UPlayerSkillMelee>());
	PlayerSkills.Add(NewObject<UPlayerSkillSwap>());
*/

	// PlayerMP
	if (PlayerStat)
	{
		PlayerMaxMP = PlayerStat->GetMaxMP();
		MPRegenRate = PlayerStat->GetMPRegenRate();
		MPRegenTime = PlayerStat->GetMPRegenTime();
		CurrentRegenTime = 0;
	}

	if(GI)
	{
		CurrentSkillData.Add(GI->GetPlayerSkillData(0));
		CurrentSkillData.Add(GI->GetPlayerSkillData(1));
		CurrentSkillData.Add(GI->GetPlayerSkillData(2));
		CurrentSkillData.Add(GI->GetPlayerSkillData(3));
	}
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime , ELevelTick TickType ,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);

	// ...

	// MP Regen
	if (!PlayerStat) return;
	int32 CurrentMP = PlayerStat->GetMP();

	if (CurrentMP < PlayerMaxMP)
	{
		CurrentRegenTime += DeltaTime;
		if (CurrentRegenTime >= MPRegenTime)
		{
			CurrentMP = CurrentMP + (MPRegenRate * DeltaTime * 100);
			PlayerStat->SetMP(CurrentMP);
			Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP , PlayerMaxMP);
			CurrentRegenTime = 0;

			UE_LOG(LogTemp , Log , TEXT("Player Use MP : %d") , CurrentMP);
		}
	}
}

void UPlayerAttackComp::Attack()
{
	if (!Player || !PlayerFSMComp) return;
	if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK)))
		return;

	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	Player->TurnPlayer();

	if (!PlayerAnim) return;
	// PlayerAnim->PlayerAttackAnimation(0);
}

void UPlayerAttackComp::CancelSkill()
{
	PlayerAttackStatus = -1;
}

void UPlayerAttackComp::ReadySkill()
{
	PlayerAttackStatus = 1;
}

void UPlayerAttackComp::CompleteSkill()
{
	if (!PlayerFSMComp) return;
	PlayerAttackStatus = 3;
	PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);

	if (!Player->GetPlayerDefaultsWidget()->GetMainQuickSlot()->IsDraggingWidget())
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		PlayerController->SetInputMode(InputMode);
	}
}

void UPlayerAttackComp::SetSkillUI(FPlayerSkillData* PlayerSkillData)
{
	if (!Player) return;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillUI(PlayerSkillData);
}

void UPlayerAttackComp::SwapSkill()
{
	int jumpSize = 0;
	for(int i = 0; i < 2; i++)
	{
		if(CurrentSkillData[i] -> ID < 2) jumpSize = 4;
		else if(CurrentSkillData[i] ->ID < 8) jumpSize = 2;
		else if(CurrentSkillData[i] -> ID >= 8) jumpSize= -4;
		
		CurrentSkillData[i] = GI -> GetPlayerSkillData(CurrentSkillData[i]->ID + jumpSize);
		//PlayerSkills[i]->ChangeSkillData(CurrentSkillData[i]);
		SetSkillUI(CurrentSkillData[i]);
	}
}

void UPlayerAttackComp::PlayerExecuteSkill(int32 SkillIndex)
{
	if (!Player || !PlayerFSMComp || !PlayerStat) return;
	if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;

	// 스킬 기능 실행
	UE_LOG(LogTemp, Log, TEXT("SkillIndex : %d"), SkillIndex)

	// MP가 있다면
	int32 CurrentMP = PlayerStat->GetMP() - CurrentSkillData[SkillIndex]->SkillCost;
	UE_LOG(LogTemp, Log, TEXT("SkillCost : %d"), CurrentSkillData[SkillIndex]->SkillCost)
	
	if (CurrentMP >= 0)
	{
		PlayerAttackStatus = 2;

		PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

		Player->TurnPlayer();

		// 스킬 애니메이션 실행
		//PlayerAnim->PlayerAttackAnimation(SkillIndex + 1);
		PlayerAnim->PlayAttackAnimation(CurrentSkillData[SkillIndex]->SkillMontage);

		// 스킬 실행
		switch (SkillIndex)
		{
		case 0 : MeleeSkill(); break;
		case 1 : RangedSkill(); break;
		case 2 : SwapSkill(); break;
		case 3 : UltSkill(); break;
		}

		// MP 소모
		PlayerStat->SetMP(CurrentMP);
		Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP , PlayerMaxMP);
	}
}


void UPlayerAttackComp::MeleeSkill()
{
	UE_LOG(LogTemp, Log, TEXT("Melee Skill : %s"), *(CurrentSkillData[0]->SkillName));
}

void UPlayerAttackComp::RangedSkill()
{
	UE_LOG(LogTemp, Log, TEXT("Ranged Skill : %s"),  *(CurrentSkillData[1]->SkillName));
}

void UPlayerAttackComp::UltSkill()
{
	// UE_LOG(LogTemp, Log, TEXT("Ult Skill : %s"),  *(CurrentSkillData[1]->SkillName));
}
