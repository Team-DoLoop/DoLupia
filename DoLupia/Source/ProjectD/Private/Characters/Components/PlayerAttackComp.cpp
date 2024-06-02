// Fill out your copyright notice in the Description page of Project Settings.


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

	Skills.SetNum(5);
	
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
	
	IgnoreAttackActors.AddUnique(Player);
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime , ELevelTick TickType ,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime , TickType , ThisTickFunction);

	// ...

	// MP Regen
	if (!PlayerStat) return;
	CurrentMP = PlayerStat->GetMP();
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

	// Skill CoolTime
	for (FSkillInfo& Skill : Skills)
	{
		if (Skill.bIsOnCooldown)
		{
			Skill.CooldownRemain -= DeltaTime;
			if (Skill.CooldownRemain < 0.0f)
			{
				Skill.CooldownRemain = 0.0f;
			}
		}
	}
}


// <---------------------- Skill Use - Color ---------------------->

void UPlayerAttackComp::InitCanUseColor()
{
	UEnum* ColorEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EUseColor"), true);
	if(!ColorEnum) return;

	UE_LOG(LogTemp, Log, TEXT("ColorEnum->NumEnums() : %d"), ColorEnum->NumEnums());
	for(int i = 0; i < ColorEnum->NumEnums(); i++)
	{
		CanUseColor.Add(static_cast<EUseColor>(ColorEnum->GetValueByIndex(i)), false);

		// 0, 2, 4, 6, 8 : None, Red, Yellow, Blue, Color
		StartIndexColor.Add(static_cast<EUseColor>(ColorEnum->GetValueByIndex(i)), i * 2); 
	}
}

void UPlayerAttackComp::SetColorUseState(EUseColor _Color, bool bCanUse)
{
	CanUseColor[_Color] = bCanUse;
}

// 퀘스트 수락 시 호출
void UPlayerAttackComp::SetSkillUseState(bool bCanUse, ESkillOpenType OpenType)
{
	// 스킬 사용 가능
	if(bCanUse)
	{
		// UI 모두 활성화 (Red로)
		CurrentSkillData[1] = GI->GetPlayerSkillData(2);
		CurrentSkillData[2] = GI->GetPlayerSkillData(3);
		CurrentSkillData[3] = GI->GetPlayerSkillData(8);
		CurrentSkillData[4] = GI->GetPlayerSkillData(9);

		CurrentSkillColor = EUseColor::RED;
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
		SetSkillUI(i-1, CurrentSkillData[i]);
		if(OpenType == ESkillOpenType::QUEST)
		{
			SetSkillCoolDownUI(i-1, 1.0f);
			Skills[i].CooldownTime = CurrentSkillData[i]->SkillCoolTime;
			Skills[i].SkillLevel = 1;
		}
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
	IgnoreAttackActors.Empty();
	IgnoreAttackActors.AddUnique(Player);

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
	SkillLevel = Skills[AttackIndex].SkillLevel;

	if(Skills.IsValidIndex(AttackIndex) && CanUseSkill(AttackIndex))
	{
		if(AttackIndex != 0)
		{
			// 쿨다운 시작
			Skills[AttackIndex].bIsOnCooldown = true;
			Skills[AttackIndex].CooldownRemain = Skills[AttackIndex].CooldownTime;
			GetWorld()->GetTimerManager().SetTimer(Skills[AttackIndex].CooldownTimerHandle,
				FTimerDelegate::CreateUObject(this, &UPlayerAttackComp::ResetCooldown, AttackIndex), Skills[AttackIndex].CooldownTime, false);
	        
			GetWorld()->GetTimerManager().SetTimerForNextTick([this, AttackIndex]()
			{
				UpdateCooldown(AttackIndex);
			});
		}
		
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
void UPlayerAttackComp::MeleeSkillAttackJudgementStart()
{
	TArray<AActor*> TargetActors;
	FVector PlayerLoc = Player->GetActorLocation();
	FVector PlayerVec = Player->GetActorForwardVector();
	PlayerVec.Z = 0;
	PlayerVec.Normalize();
	FVector BoxPos = FVector((SkillRange.X * PlayerVec.X)+ PlayerLoc.X, (SkillRange.Y * PlayerVec.Y) + PlayerLoc.Y, PlayerLoc.Z);

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
			// IgnoreAttackActors에 없다면
			if(!IgnoreAttackActors.IsValidIndex(IgnoreAttackActors.Find(Monster)))
			{
				IgnoreAttackActors.AddUnique(Monster);
				Monster->OnMyTakeDamage(SkillDamage * SkillLevel);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster"), *Monster->GetName());
			}
		}
	}
}

void UPlayerAttackComp::MeleeSkillAttackJudgementEnd()
{
	IgnoreAttackActors.Empty();
	IgnoreAttackActors.AddUnique(Player);
}

void UPlayerAttackComp::MeleeSkill()
{
	UE_LOG(LogTemp, Log, TEXT("Melee Skill : %s"), *(CurrentSkillData[0]->SkillName));
}

void UPlayerAttackComp::RangedSkill()
{
	UE_LOG(LogTemp, Log, TEXT("Ranged Skill : %s"),  *(CurrentSkillData[1]->SkillName));
}

EUseColor UPlayerAttackComp::FindSkillColor(EUseColor _CurrentColor)
{
	EUseColor _NextColor = static_cast<EUseColor>(static_cast<int32>(_CurrentColor) + 1);

	switch (_CurrentColor)
	{
	case EUseColor::RED : _NextColor = EUseColor::YELLOW; break;
	case EUseColor::YELLOW : _NextColor = EUseColor::BLUE; break;
	case EUseColor::BLUE : _NextColor = EUseColor::RED; break;
	}

	// 해금이 안되어 있다면 무조건 Red 반환
	if(!CanUseColor[_NextColor]) return EUseColor::RED;
	
	return _NextColor;
}

void UPlayerAttackComp::SwapSkill()
{
	CurrentSkillColor = FindSkillColor(CurrentSkillColor);
	int32 NextSkillIndex = StartIndexColor[CurrentSkillColor];
	
	for(int i = 0; i < 2; i++)
	{
		// 0은 기본 공격이라 1부터 시작
		CurrentSkillData[i+1] = GI -> GetPlayerSkillData(NextSkillIndex + i);
		SetSkillUI(i, CurrentSkillData[i+1]);
	}
}

void UPlayerAttackComp::SetSkillUI(int32 SlotIndex, FPlayerSkillData* PlayerSkillData)
{
	if (!Player) return;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillUI(SlotIndex, PlayerSkillData);
}

void UPlayerAttackComp::SetSkillCoolDownUI(int32 SlotIndex, float CoolTime)
{
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillCoolTimeUI(SlotIndex, CoolTime);
}

void UPlayerAttackComp::SetSkillAttackData(FPlayerSkillData* PlayerSkillData)
{
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

void UPlayerAttackComp::UpdateCooldown(int32 AttackIndex)
{
	if (Skills.IsValidIndex(AttackIndex) && Skills[AttackIndex].bIsOnCooldown)
	{
		Skills[AttackIndex].CooldownRemain -= GetWorld()->GetDeltaSeconds();

		if (Skills[AttackIndex].CooldownRemain <= 0.0f)
		{
			ResetCooldown(AttackIndex);
		}
		else
		{
			SetSkillCoolDownUI(AttackIndex-1, GetCooldownPercent(AttackIndex));
			GetWorld()->GetTimerManager().SetTimerForNextTick([this, AttackIndex]()
			{
				UpdateCooldown(AttackIndex);
			});
		}
	}
}


// <---------------------- Skill Upgrade ---------------------->

void UPlayerAttackComp::GetSkillUpgradePoint(int32 SkillIndex)
{
	// 스킬 업그레이드 UI
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->ShowSkillUpgradeUI(SkillIndex-1);
}

void UPlayerAttackComp::SkillUpgrade(int32 SkillIndex)
{
	Skills[SkillIndex].SkillLevel = Skills[SkillIndex].SkillLevel + 1;
	if(Skills[SkillIndex].SkillLevel >= 5) Skills[SkillIndex].SkillLevel = 5;
}


// <---------------------- Skill CoolDown ---------------------->

void UPlayerAttackComp::ResetCooldown(int32 AttackIndex)
{
	if (Skills.IsValidIndex(AttackIndex))
	{
		Skills[AttackIndex].bIsOnCooldown = false;
		Skills[AttackIndex].CooldownRemain = 0.0f;
		UpdateCooldown(AttackIndex);
		UE_LOG(LogTemp, Warning, TEXT("Skill %d cooldown reset."), AttackIndex);
	}
}

bool UPlayerAttackComp::CanUseSkill(int32 AttackIndex)
{
	// MP가 있다면
	CurrentMP = PlayerStat->GetMP() - SkillCost;
	UE_LOG(LogTemp, Log, TEXT("SkillCost : %d"), SkillCost)

	// 평타거나 현재 색깔이 있고 MP가 있는 스킬이라면 공격 실행
	if (AttackIndex == 0 || (CurrentSkillColor != EUseColor::NONE && CurrentMP >= 0))
	{
		if(!Skills[AttackIndex].bIsOnCooldown) return true;
	}
	return false;
}

float UPlayerAttackComp::GetCooldownPercent(int32 AttackIndex)
{
	if (Skills.IsValidIndex(AttackIndex) && Skills[AttackIndex].CooldownTime > 0)
	{
		return 1.0f - (Skills[AttackIndex].CooldownRemain / Skills[AttackIndex].CooldownTime);
	}
	return 0.0f;
}