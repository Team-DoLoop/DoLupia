﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "BlueprintEditor.h"
#include "CollisionDebugDrawingPublic.h"
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
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monsters/Monster.h"
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
		CurrentSkillData.Add(GI->GetPlayerSkillData(1));		// 평타 맨 앞에 넣기
		for(int i = 0; i < SkillCount; i++)
		{
			CurrentSkillData.Add(GI->GetPlayerSkillData(0));	// 스킬 사용 못할 때 data 넣기
		}
	}

	InitCanUseColor();
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
		}
	}
}


// <---------------------- Skill Use - Color ---------------------->

void UPlayerAttackComp::InitCanUseColor()
{
	UEnum* ColorEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUseColor"), true);
	if(ColorEnum) return;

	for(int i = 0; i < ColorEnum->NumEnums()-1; i++)
	{
		CanUseColor.Add(static_cast<EUseColor>(ColorEnum->GetValueByIndex(i)), -1);
	}
}

void UPlayerAttackComp::SetColorUseState(EUseColor _Color, bool bCanUse)
{
	CanUseColor[_Color] = bCanUse;
}

// 퀘스트나 무기 장착 상태 변화 시 호출
void UPlayerAttackComp::SetSkillUseState(bool bCanUse)
{
	// 스킬 사용 가능
	if(bCanUse)
	{
		// UI 모두 활성화
		CurrentSkillData[1] = GI->GetPlayerSkillData(1);
		CurrentSkillData[2] = GI->GetPlayerSkillData(2);
		CurrentSkillData[3] = GI->GetPlayerSkillData(8);
		CurrentSkillData[4] = GI->GetPlayerSkillData(9);
	}
	else
	{
		// UI 비활성화
		for(int i = 1; i <= SkillCount; i++)
		{
			CurrentSkillData[i] = GI->GetPlayerSkillData(0);	// 스킬 사용 X 데이터
		}
	}

	for(int i = 1; i <= SkillCount; i++)
	{
		SetSkillUI(i, CurrentSkillData[i]);
	}
}

// <---------------------- Attack ---------------------->

void UPlayerAttackComp::Attack()
{
	/*
	if (!Player || !PlayerFSMComp) return;
	if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK)))
		return;

	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	Player->TurnPlayer();

	if (!PlayerAnim) return;
	PlayerAnim->PlayAttackAnimation(AutoAttackMontage);
	//PlayerAnim->PlayerAttackAnimation(0);
	*/
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

void UPlayerAttackComp::PlayerExecuteAttack(int32 AttackIndex)
{
	if (!Player || !PlayerFSMComp || !PlayerStat) return;
	if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK))) return;

	SetSkillAttackData(CurrentSkillData[AttackIndex]);

	// MP가 있다면
	int32 CurrentMP = PlayerStat->GetMP() - SkillCost;
	UE_LOG(LogTemp, Log, TEXT("SkillCost : %d"), SkillCost)

	// 평타거나 현재 색깔이 있고 MP가 있는 스킬이라면 공격 실행
	if (AttackIndex == 0 || (CurrentSkillColor != EUseColor::NONE && CurrentMP >= 0))
	{
		PlayerAttackStatus = 2;
		PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

		Player->TurnPlayer();

		// 공격 애니메이션 실행
		//PlayerAnim->PlayerAttackAnimation(SkillIndex + 1);
		PlayerAnim->PlayAttackAnimation(SkillMontage);

		// 공격 실행
		switch (AttackIndex)
		{
		case 0 : Attack(); break;
		case 1 : MeleeSkill(); break;
		case 2 : RangedSkill(); break;
		case 3 : SwapSkill(); break;
		case 4 : UltSkill(); break;
		default: break;
		}

		// MP 소모
		PlayerStat->SetMP(CurrentMP);
		Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP , PlayerMaxMP);
	}
}

// 애니메이션 노티파이로 호출하는 근거리 스킬 공격 생성 함수
void UPlayerAttackComp::MeleeSkillAttackJudgement()
{
	TArray<AActor*> TargetActors;
	FVector PlayerLoc = Player->GetActorLocation();
	FVector BoxPos = FVector(SkillRange.X + PlayerLoc.X, SkillRange.Y + PlayerLoc.Y, PlayerLoc.Z);

	// 확인용 박스
	DrawDebugBox(GetWorld(), BoxPos, SkillRange, FColor::Red, false, 3.0f);

	// 공격 판정
	UKismetSystemLibrary::BoxOverlapActors(GetWorld(), BoxPos, SkillRange,
		TArray<TEnumAsByte<EObjectTypeQuery>>(), nullptr, TArray<AActor*>(),
		TargetActors);
	for(auto TargetActor : TargetActors)
	{
		if (AMonster* Monster = Cast<AMonster>(TargetActor))
		{
			Monster->OnMyTakeDamage(SkillDamage);
			UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster"), *Monster->GetName());
		}
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

void UPlayerAttackComp::SwapSkill()
{
	int32 SwitchUINum = 0;				// 바꿀 UI 개수
	int32 NextSkillIndex = 0;			// 다음 스킬 Index

	switch (CurrentSkillColor)
	{
	case EUseColor::NONE : break;		// 스킬에서는 NONE에서 시작할 수가 없음
	case EUseColor::RED : break;
	case EUseColor::YELLOW : break;
	case EUseColor::BLUE : break;
	}
	
	int jumpSize = 0;
		/*
	for(int i = 1; i < 3; i++)
	{
		// 스킬 습득에 따라 수정 예정
		if(CurrentSkillData[i] -> ID < 2) jumpSize = 4;
		else if(CurrentSkillData[i] ->ID < 8) jumpSize = 2;
		else if(CurrentSkillData[i] -> ID >= 8) jumpSize= -4;
		
		CurrentSkillData[i] = GI -> GetPlayerSkillData(CurrentSkillData[i]->ID + jumpSize);
		//PlayerSkills[i]->ChangeSkillData(CurrentSkillData[i]);
		SetSkillUI(i, CurrentSkillData[i]);
	}
	*/
}

void UPlayerAttackComp::SetSkillUI(int32 SlotIndex, FPlayerSkillData* PlayerSkillData)
{
	if (!Player) return;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillUI(SlotIndex-1, PlayerSkillData);
}

void UPlayerAttackComp::SetSkillAttackData(FPlayerSkillData* PlayerSkillData)
{
	SkillLevel = PlayerSkillData->SkillLevel;
	SkillCost = PlayerSkillData->SkillCost;
	SkillCoolTime = PlayerSkillData->SkillCoolTime;
	SkillMontage = PlayerSkillData->SkillMontage;
	SkillDamage = PlayerSkillData->SkillDamage;
	SkillRange = PlayerSkillData->SkillRange;
}


void UPlayerAttackComp::UltSkill()
{
	// UE_LOG(LogTemp, Log, TEXT("Ult Skill : %s"),  *(CurrentSkillData[1]->SkillName));
}

