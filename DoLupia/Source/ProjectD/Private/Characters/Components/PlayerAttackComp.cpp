// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "ProjectDGameInstance.h"
#include "Characters/PlayerStat.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Skill/PlayerSkillElecBlast.h"
#include "Characters/Skill/PlayerSkillLightning.h"
#include "Characters/Skill/PlayerSkillShield.h"
#include "Characters/Skill/PlayerSkillUlt.h"
#include "Characters/Skill/PlayerSkillWaterBlade.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Items/Sword/SwordBase.h"
#include "Kismet/GameplayStatics.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"
#include "Pooling/SoundManager.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"
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

	if(PlayerAnim)
	{
		PlayerAnim->OnNextAttackCheck.AddUObject(this, &UPlayerAttackComp::NextAttackCheck);
	}
	
	// PlayerMP
	if (PlayerStat)
	{
		PlayerMaxMP = PlayerStat->GetMaxMP();
		//MPRegenRate = PlayerStat->GetMPRegenRate();
		//MPRegenTime = PlayerStat->GetMPRegenTime();
		//CurrentRegenTime = 0;
	}

	CantSkill.SetNum(5);
	for(int i = 0; i < CantSkill.Num(); i++) CantSkill[i] = new FSkillInfo();

	// 여기 누수나는 코드
	AutoSkill = new FSkillInfo();
	RedQSkill = new FSkillInfo();
	RedWSkill = new FSkillInfo();
	YellowQSkill = new FSkillInfo();
	YellowWSkill = new FSkillInfo();
	BlueQSkill = new FSkillInfo();
	BlueWSkill = new FSkillInfo();
	SwapSkill = new FSkillInfo();
	UltSkill = new FSkillInfo();
	
	if(GI)
	{
		CantSkill[0]->SkillData	= GI->GetPlayerSkillData(1);			// 스킬 사용 못할 때 data 넣기
		for(int i = 1; i <= SkillCount; i++)
		{
			CantSkill[i]->SkillData = GI->GetPlayerSkillData(0);
		}

		AutoSkill->SkillData = GI->GetPlayerSkillData(1);			// Auto
		RedQSkill->SkillData = GI->GetPlayerSkillData(2);			// Red
		RedWSkill->SkillData =GI->GetPlayerSkillData(3);
		YellowQSkill->SkillData = GI->GetPlayerSkillData(4);			// Yellow
		YellowWSkill->SkillData = GI->GetPlayerSkillData(5);			
		BlueQSkill->SkillData = GI->GetPlayerSkillData(6);			// Blue
		BlueWSkill->SkillData = GI->GetPlayerSkillData(7);
		SwapSkill->SkillData = GI->GetPlayerSkillData(8);
		UltSkill->SkillData = GI->GetPlayerSkillData(9);				// Ult
	}

	InitCanUseColor();
	InitSkillLevel();
	
	IgnoreAttackActors.AddUnique(Player);

	bIsShowDebugLine = Player->GetbIsShowDebugLine();
}

void UPlayerAttackComp::InitSkillUI()
{
	// 스킬 UI 초기화 함수 (PlayerSkillSlotWidget에서 생성 후에 호출)
	if(CanUseColor[EUseColor::RED])
	{
		SetSkillUseState(true,ESkillOpenType::NONE);
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
	// CurrentMP = PlayerStat->GetMP();
	/*
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
	*/
	
	// SkillCoolUI
	SetSkillCoolDownUI();
}


// <---------------------- Skill Use - Color ---------------------->

void UPlayerAttackComp::InitCanUseColor()
{
	if(!GI) return;

	CanUseColor = GI->GetCanUseColor();
	
	IsUnLockSwap = CanUseColor[EUseColor::YELLOW];
	IsUnLockUlt = CanUseColor[EUseColor::BLUE];
}

void UPlayerAttackComp::SetColorUseState(EUseColor _Color, bool bCanUse)
{
	if(!GI) return;
	CanUseColor[_Color] = bCanUse;
	GI->SetCanUseColor(_Color, bCanUse);
	
	switch (_Color)
	{
	case EUseColor::YELLOW :
		{
			// E 스킬 잠금 해제 or 잠그기
			IsUnLockSwap = bCanUse;
			SetSkillLockUI(3, !bCanUse);
			break;
		}
	case EUseColor::BLUE :
		{
			// 궁 잠금 해제 or 잠그기
			IsUnLockUlt = bCanUse;
			SetSkillLockUI(4, !bCanUse);
			break;
		}
	default: break;
	}
}

// 퀘스트 수락 시 호출
void UPlayerAttackComp::SetSkillUseState(bool bCanUse, ESkillOpenType OpenType)
{
	auto CurrentSkillData = CantSkill;
	
	// 스킬 사용 가능
	if(bCanUse)
	{
		CurrentSkillColor = EUseColor::RED;
		CurrentSkillData.Add(AutoSkill);
		CurrentSkillData[1] = RedQSkill;
		CurrentSkillData[2] = RedWSkill;
		CurrentSkillData[3] = SwapSkill;
		CurrentSkillData[4] = UltSkill;
	}
	else
	{
		CurrentSkillColor = EUseColor::NONE;
	}
	
	ChangePlayerColor(CurrentSkillColor);
	
	for(int i = 1; i <=SkillCount; i++)
	{
		SetSkillUI(i-1, CurrentSkillData[i]);

		SetSkillLockUI(i, (PlayerStat->GetMP() >= PlayerMaxMP));
	}
}

void UPlayerAttackComp::SetSkillLockUI(int32 SkillKeyIndex, bool IsSkillLock)
{
	// E 스킬인데 해제되지 않았다면
	if(SkillKeyIndex == 3 && !IsUnLockSwap) IsSkillLock = true;

	// 궁인데 해제되지 않았다면
	else if(SkillKeyIndex == 4 && !IsUnLockUlt) IsSkillLock = true;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->SetSkillLockUI(SkillKeyIndex, IsSkillLock);
}

// <---------------------- Attack ---------------------->

void UPlayerAttackComp::PlayCameraShake()
{
	// 카메라 쉐이크가 있다면
	if(SkillCameraShake)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(SkillCameraShake, 1.0f);
}

void UPlayerAttackComp::Attack(FSkillInfo* _TempInfo)
{

}

void UPlayerAttackComp::FirstAttack(FSkillInfo* _TempInfo, int32 SkillKeyIndex)
{
	if(SkillKeyIndex != 3) CurrentSkillInfo = _TempInfo;
	SetSkillData(_TempInfo);
	SetSpawnLocation();
	AttackStartComboState();
	
	// UI
	SkillKeyIndex_Combo = SkillKeyIndex;
	SetComboAttackUI(SkillKeyIndex, true);

	// 차징 스킬이라면
	if(IsSkillCharging)
	{
		// 차징 UI 띄우기
		Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->StartChargingSkill();
		IsChargingInputOn = true;

		// 차징 타이머 시작
		GetWorld()->GetTimerManager().SetTimer(ChargingTimerHandle, ChargingTime, false);
	}
	
	Player->TurnPlayer();
	
	// 공격 애니메이션 실행`
	PlayerAnim->PlayAttackAnimation(SkillMontage);
	PlayerAnim->JumpToAttackMontageSection(CurrentCombo); // CurrentCombo = 1
	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK_ONLY);
	
	// MP 소모
	PlayerStat->SetMP(PlayerStat->GetMP() + _TempInfo->SkillData->SkillCost);
	CurrentMP = PlayerStat->GetMP();
	Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP , PlayerMaxMP);
	
	IgnoreAttackActors.Empty();
	IgnoreAttackActors.AddUnique(Player);
}

void UPlayerAttackComp::CompleteSkill()
{
	if (!PlayerFSMComp) return;

	if(IsSkillCharging && IsChargingInputOn)
	{
		PlayerChargingEndSkill();
	}
	else
	{
		PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);
	
		IgnoreAttackActors.Empty();
		IgnoreAttackActors.AddUnique(Player);
	
		SetComboAttackUI(SkillKeyIndex_Combo, false);
		SkillKeyIndex_Combo = -1;
	}
	
	AttackEndState();

	if (!Player->GetPlayerDefaultsWidget()->GetMainQuickSlot()->IsDraggingWidget())
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		PlayerController->SetInputMode(InputMode);
	}
}


// <------------------------------ Skill ------------------------------>

void UPlayerAttackComp::PlayerExecuteAttack(int32 SkillKeyIndex)
{
	if (!Player || !PlayerFSMComp || !PlayerStat) return;
	if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK_ONLY))) return;
	
	FSkillInfo* TempSkill = GetSkillInfo(CurrentSkillColor, SkillKeyIndex);
	EPlayerState CurrentState = PlayerFSMComp->GetCurrentState();

	if(!(TempSkill && CanUseSkill(TempSkill)))
	{
		if (ASoundManager* SoundManager = ASoundManager::GetInstance(GetWorld()))
		{
			if(CantAttackSoundWave) SoundManager->PlaySoundWave( CantAttackSoundWave, EEffectSound::EffectSound1, Player->GetActorLocation(), SkillVolume );
		}
		return;
	}

	// 첫 공격이라면 바로 실행
	if (CurrentState != EPlayerState::ATTACK_ONLY && CurrentState != EPlayerState::ATTACK_WITH)
	{
		UE_LOG(LogTemp, Log, TEXT("First Combo Attack"));
		FirstAttack(TempSkill, SkillKeyIndex);
	}
	// 첫 공격이 아니고 콤보 구간이라면
	else if(CurrentState == EPlayerState::ATTACK_ONLY)
	{
		// UE_LOG(LogTemp, Log, TEXT("In Combo State Press"));
		// 만약 콤보 가능 구간이라면
		if(CanNextCombo)
		{
			// 콤보 공격 입력
			// UE_LOG(LogTemp, Log, TEXT("IsComboInputOn = true"));

			// 그 중 첫번째 눌린 경우에는 Press UI 뜨게
			if(!IsComboInputOn) SetComboAttackUI(SkillKeyIndex, true);
			IsComboInputOn = true;
		}
	}
	// 콤보 공격 구간은 아니지만 공격 중이라면
	else if(CurrentState == EPlayerState::ATTACK_WITH)
	{
		// 원래 스킬은 사용 못하고
		if(CurrentSkillInfo != TempSkill)
		{
			FirstAttack(TempSkill, SkillKeyIndex);
		}
	}
		
	SetSkillCoolDownUI();

	if(SkillKeyIndex == 3)
	{
		ExecuteSwapSkill();
	}
}

void UPlayerAttackComp::PlayerQuitSkill(int32 AttackIndex)
{

}


// <------------------------------ Skill Melee ------------------------------>

// 애니메이션 노티파이로 호출하는 근거리 스킬 공격 생성 함수
void UPlayerAttackComp::MeleeSkillAttackJudgementStart()
{
	TArray<AActor*> TargetActors;
	FVector SwordLoc = Player->GetGadgetComp()->GetSword()->GetActorLocation();
	FVector PlayerVec = Player->GetActorForwardVector();
	PlayerVec.Z = 0;
	PlayerVec.Normalize();
	FVector BoxPos = FVector((SkillRange.X * PlayerVec.X)+ SwordLoc.X, (SkillRange.Y * PlayerVec.Y) + SwordLoc.Y, SwordLoc.Z);
	auto BoxRot = PlayerVec.Rotation().Quaternion();
	
	// 확인용 박스
	if(bIsShowDebugLine) DrawDebugBox(GetWorld(), BoxPos, SkillRange, BoxRot, FColor::Red, false, 3.0f);

	RandDamage = FMath::RandRange(SkillDamage/2, SkillDamage) * PlayerStat->GetATK();
	
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
				Monster->OnMyTakeDamage(RandDamage * SkillLevel);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster : %d"), *Monster->GetName(), RandDamage * SkillLevel);
			}
		}
		
		else if (ABossMonster* BossMonster = Cast<ABossMonster>(TargetActor))
		{
			// IgnoreAttackActors에 없다면
			if(!IgnoreAttackActors.IsValidIndex(IgnoreAttackActors.Find(BossMonster)))
			{
				IgnoreAttackActors.AddUnique(BossMonster);
				BossMonster->OnMyTakeDamage(RandDamage * SkillLevel);
				UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster : %d"), *BossMonster->GetName(), RandDamage * SkillLevel);
			}
		}
	}
}

void UPlayerAttackComp::MeleeSkillAttackJudgementEnd()
{
	IgnoreAttackActors.Empty();
	IgnoreAttackActors.AddUnique(Player);
}



// <------------------------------ Skill Ranged ------------------------------>

void UPlayerAttackComp::RangedSkillAttackJudgementStart()
{
	RandDamage = FMath::RandRange(SkillDamage/2, SkillDamage) * PlayerStat->GetATK();
	if(SkillKeyIndex_Combo == 1)
	{
		if(!PlayerElecBlastFactory) return;

		PlayerElecBlast = GetWorld()->SpawnActor<APlayerSkillElecBlast>(PlayerElecBlastFactory, SpawnLocation, FRotator(0));
		PlayerElecBlast->SetSkillDamage(SkillLevel * RandDamage);

		GetWorld()->GetTimerManager().SetTimer(ElecBlastTimerHandle, this, &UPlayerAttackComp::BlastAttackEnd, ElecBlastTime, false);
	}
	
	else if(SkillKeyIndex_Combo == 2)
	{
		if(!PlayerLightningFactory) return;

		PlayerLightning = GetWorld()->SpawnActor<APlayerSkillLightning>(PlayerLightningFactory, SpawnLocation, FRotator(0));
		PlayerLightning->SetSkillDamage(SkillLevel * RandDamage);
	}
}

void UPlayerAttackComp::RangedSkillAttackJudgmentEnd()
{
	if(SkillKeyIndex_Combo == 2)
	{
		if(PlayerLightning) PlayerLightning->Destroy();
	}
}

void UPlayerAttackComp::BlastAttackEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(ElecBlastTimerHandle);
	if(PlayerElecBlast) PlayerElecBlast->Destroy();
}


// <------------------------------ Skill Shield ------------------------------>

void UPlayerAttackComp::ShieldSkillStart()
{
	if(!PlayerShieldFactory || !PlayerFSMComp) return;

	const FName& ShieldSocket( TEXT( "ShieldSocket" ) );
	FVector PlayerLoc = Player->GetActorLocation();
	PlayerLoc.Z = PlayerLoc.Z + 30.0f;
	PlayerShield = GetWorld()->SpawnActor<APlayerSkillShield>(PlayerShieldFactory, PlayerLoc, FRotator(0));
	// PlayerShield->SetActorScale3D(FVector(0.4f));
	PlayerShield->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ShieldSocket);
	GetWorld()->GetTimerManager().SetTimer(ShieldTimerHandle, this, &UPlayerAttackComp::ShieldSkillEnd, ShieldTime, false);

	RandDamage = FMath::RandRange(SkillDamage/2, SkillDamage) * PlayerStat->GetATK();
	PlayerShield->SetSkillDamage(SkillLevel * RandDamage);
	
	PlayerFSMComp->ChangePlayerShieldState(EPlayerShieldState::SHIELD);
}

void UPlayerAttackComp::ShieldSkillEnd()
{
	if(!PlayerShield || !PlayerFSMComp) return;
	
	PlayerFSMComp->ChangePlayerShieldState(EPlayerShieldState::NONE);
	GetWorld()->GetTimerManager().ClearTimer(ShieldTimerHandle);
	PlayerShield->Destroy();
}



// <------------------------------ Skill WaterBlade ------------------------------>

void UPlayerAttackComp::PlayerWaterBladeSkill()
{
	if(!PlayerWaterBladeFactory) return;

	RandDamage = FMath::RandRange(SkillDamage/2, SkillDamage) * PlayerStat->GetATK();
	
	PlayerWaterBlade = GetWorld()->SpawnActor<APlayerSkillWaterBlade>(PlayerWaterBladeFactory, Player->GetActorLocation(), FRotator(0));
	PlayerWaterBlade->SetSkillDirection(Player->GetActorForwardVector());
	PlayerWaterBlade->SetSkillRot(Player->GetActorRotation());
	PlayerWaterBlade->SetSkillDamage(SkillLevel * RandDamage);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
	DestroyWaterBlade();
}, WaterBladeRemainTime, false);
}

void UPlayerAttackComp::DestroyWaterBlade()
{
	if(PlayerWaterBlade) PlayerWaterBlade->Destroy();
}


// <------------------------------ Skill Swap ------------------------------>

void UPlayerAttackComp::ExecuteSwapSkill()
{
	// 그 전에 눌렀던 스킬 쿨다운 시작
	if(CurrentSkillInfo)
	{
		AttackEndState();
	}
	SetComboAttackUI(SkillKeyIndex_Combo, false);
	
	CurrentSkillColor = FindSkillColor(CurrentSkillColor);
	for(int i = 0; i < 2; i++)
	{
		FSkillInfo* _TempSkill = GetSkillInfo(CurrentSkillColor, i+1);
		SetSkillUI(i, _TempSkill);
	}

	if (ASoundManager* SoundManager = ASoundManager::GetInstance(GetWorld()))
	{
		if(SwapSoundWave) SoundManager->PlaySoundWave( SwapSoundWave, EEffectSound::EffectSound1, Player->GetActorLocation(), SkillVolume );
	}

	ChangePlayerColor(CurrentSkillColor);
	SetSkillCoolDownUI();
}

void UPlayerAttackComp::ChangePlayerColor(EUseColor _CurrentColor)
{
	// 스킬의 색깔에 따라 플레이어 몸 색상 변경

	int32 depth = 0;
	bool IsColor = false;
	switch (_CurrentColor)
	{
		case EUseColor::RED : depth = 1; IsColor = true; break;
		case EUseColor::YELLOW : depth = 3; IsColor = true; break;
		case EUseColor::BLUE : depth = 2; IsColor = true; break;
		default: depth = 0; IsColor = false; break;
	}

	if(Player)
	{
		if(auto _Gadet = Player->GetGadgetComp())
		{
			if(auto _Sword = _Gadet->GetSword())
			{
				_Sword->GetItemStaticMesh()->SetCustomDepthStencilValue( depth );
				_Sword->GetItemStaticMesh()->SetRenderCustomDepth( IsColor );
			}
		}
	}
}

void UPlayerAttackComp::SetSkillUI(int32 SlotIndex, FSkillInfo* PlayerSkillInfo)
{
	if (!Player) return;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillUI(SlotIndex, PlayerSkillInfo);
	UpdateSkillLevel(SlotIndex + 1, PlayerSkillInfo);
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


// <------------------------------ Ult ------------------------------>

void UPlayerAttackComp::ExecuteUltSkill()
{
	if(!PlayerUltFactory) return;
	
	PlayerUlt = GetWorld()->SpawnActor<APlayerSkillUlt>(PlayerUltFactory, SpawnLocation, FRotator(0));
	// PlayerUlt->SetDamage(SkillDamage);
	GetWorld()->GetTimerManager().SetTimer(UltTimerHandle, this, &UPlayerAttackComp::ExecuteUltEnd, UltTime, false);
}

void UPlayerAttackComp::ExecuteUltEnd()
{
	if(!PlayerUlt) return;
	
	GetWorld()->GetTimerManager().ClearTimer(UltTimerHandle);
	PlayerUlt->Destroy();
}


// <------------------------------ Charging Skill ------------------------------>

void UPlayerAttackComp::PlayerChargingSkill()
{
	if(!IsSkillCharging) return;
	
	if(IsChargingInputOn)
	{
		float RemainingTime = 1 - (GetWorld()->GetTimerManager().GetTimerRemaining(ChargingTimerHandle)) / ChargingTime;
		Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->UpdateChargingSkill(RemainingTime, CanChargingSkill);
	}
}

void UPlayerAttackComp::PlayerChargingEndSkill()
{
	if(!IsSkillCharging || !IsChargingInputOn) return;

	if(!CanChargingSkill) 
	{
		// 차징 중간에 끊겼다면
		PlayerAnim->StopMontage();
		IsChargingInputOn = false;
	}

	else
	{
		// 차징 공격 실행
		Player->TurnPlayer();
		PlayerAnim->PlayAttackAnimation(SkillMontage);
		PlayerAnim->JumpToAttackMontageSection(2);
		CanChargingSkill = false;

		// 스킬 쿨타임 돌게
		StartCooldown(CurrentSkillInfo->CooldownTimerHandle, CurrentSkillInfo->SkillData->SkillCoolTime);
	}

	// 차징 UI 끄기
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->EndChargingSkill();
	if(ChargingTimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(ChargingTimerHandle);
}

void UPlayerAttackComp::NextChargingCheck()
{
	if(!IsChargingInputOn) return;

	UE_LOG(LogTemp, Log, TEXT("NextChargingCheck"));
	
	CanChargingSkill = true;
}

float UPlayerAttackComp::GetChargingPercent(float RemainingTime, float _ChargingTime)
{
	if (_ChargingTime > 0)
	{
		return 1- (RemainingTime / _ChargingTime);
	}
	
	return 0.0f;
}

// <---------------------- Skill Data ---------------------->

FSkillInfo* UPlayerAttackComp::GetSkillInfo(EUseColor _Color, int32 SkillKeyIndex)
{
	switch (SkillKeyIndex)
	{
	case 0: return AutoSkill;
	case 3 : return SwapSkill;
	case 4: return UltSkill;
	}
	
	switch (_Color)
	{
	case EUseColor::RED :
		{
			if(SkillKeyIndex == 1) return RedQSkill;
			if(SkillKeyIndex == 2) return RedWSkill;
		}

	case EUseColor::YELLOW :
		{
			if(SkillKeyIndex == 1) return YellowQSkill;
			if(SkillKeyIndex == 2) return YellowWSkill;
		}

	case EUseColor::BLUE :
		{
			if(SkillKeyIndex == 1) return BlueQSkill;
			if(SkillKeyIndex == 2) return BlueWSkill;
		}
	}

	return nullptr;
}

void UPlayerAttackComp::SetSkillData(FSkillInfo* _TempInfo)
{
	auto _SkillData = _TempInfo->SkillData;
	
	SkillMontage = _SkillData->SkillMontage;
	SkillCameraShake = _SkillData->SkillCameraShake;
	SkillDamage = _SkillData->SkillDamage;
	SkillRange = _SkillData->SkillRange;
	SkillMaxCombo = _SkillData->SkillMaxCombo;
	SkillLevel = _TempInfo->SkillLevel;
	SkillMaxRange = _SkillData->SkillMaxRange;
	IsSkillCharging = _SkillData->SkillChargingData.IsChargingSkill;
}

void UPlayerAttackComp::SetSpawnLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!bHitSuccessful) return;

	FVector MouseLocation = Hit.Location;
	FVector PlayerLoc = Player->GetActorLocation();
	float Distance = FVector::Dist(PlayerLoc, MouseLocation);
	
	if (Distance > SkillMaxRange)
	{
		FVector Direction = (MouseLocation - PlayerLoc).GetSafeNormal();
		SpawnLocation = PlayerLoc + Direction * SkillMaxRange;
	}
	else  SpawnLocation = MouseLocation;
}


// <---------------------- Skill Upgrade ---------------------->

void UPlayerAttackComp::InitSkillLevel()
{
	if(!GI) return;
	auto _SkillLevel = GI->GetPlayerSkillLevel();

	RedQSkill->SkillLevel = _SkillLevel[0];
	RedWSkill->SkillLevel = _SkillLevel[1];
	YellowQSkill->SkillLevel = _SkillLevel[2];
	YellowWSkill->SkillLevel = _SkillLevel[3];
	BlueQSkill->SkillLevel = _SkillLevel[4];
	BlueWSkill->SkillLevel = _SkillLevel[5];
}

void UPlayerAttackComp::GetSkillUpgradePoint(EUseColor _Color, int32 SkillKeyIndex)
{
	FSkillInfo* _TempSkill = GetSkillInfo(_Color, SkillKeyIndex);
		
	if(_TempSkill)
	{
		if(_TempSkill->SkillLevel < 5)
		{
			_TempSkill->SkillLevel = _TempSkill->SkillLevel + 1;
			GI->SetPlayerSkillLevel(_Color, SkillKeyIndex, _TempSkill->SkillLevel);
		}
		
		if(_Color == CurrentSkillColor) UpdateSkillLevel(SkillKeyIndex, _TempSkill);
		UE_LOG(LogTemp,Log,TEXT("Get GetSkillUpgradePoint"));
	}
}

void UPlayerAttackComp::UpdateSkillLevel(int32 SkillKeyIndex, FSkillInfo* _TempSkill)
{
	// 스킬 레벨 UI 업데이트
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillLevelUI(SkillKeyIndex, _TempSkill->SkillLevel);
}


// <---------------------- Skill CoolDown ---------------------->

void UPlayerAttackComp::StartCooldown(FTimerHandle& CooldownTimerHandle, float _CoolTime)
{
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, _CoolTime, false);
}

float UPlayerAttackComp::GetCooldownPercent(float RemainingTime, float _SkillCoolTime)
{
	if (_SkillCoolTime > 0)
	{
		return (RemainingTime / _SkillCoolTime);
	}
	
	return 0.0f;
}

void UPlayerAttackComp::SetSkillCoolDownUI()
{
	if(CurrentSkillColor == EUseColor::NONE) return;
	for(int i = 0; i < 4; i++)
	{
		auto _TempInfo = GetSkillInfo(CurrentSkillColor, i + 1);
		float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(_TempInfo->CooldownTimerHandle);
		Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillCoolTimeUI(i, GetCooldownPercent(RemainingTime, _TempInfo->SkillData->SkillCoolTime) );
	}
}

bool UPlayerAttackComp::CanUseSkill(FSkillInfo* _TempSkill)
{
	// 게이지가 100이라면
	if(_TempSkill != AutoSkill && PlayerStat->GetMP() >= PlayerMaxMP) return false;

	// E 스킬인데 잠금 해제가 안되었다면
	if(_TempSkill == SwapSkill && !IsUnLockSwap) return false;
	
	// 궁인데 잠금 해제가 안됐다면
	if(_TempSkill == UltSkill && !IsUnLockUlt) return false;
	
	// 평타거나 현재 색깔이 있고 MP가 있는 스킬이라면 공격 실행
	if (_TempSkill == AutoSkill || (CurrentSkillColor != EUseColor::NONE))
	{
		return (!GetWorld()->GetTimerManager().IsTimerActive(_TempSkill->CooldownTimerHandle));
		//	if(!_TempSkill->bIsOnCooldown) return true;
	}
	return false;
}

void UPlayerAttackComp::TurnToAttackWithState()
{
	if(PlayerFSMComp)
	{
		if (!(PlayerFSMComp->CanChangeState(EPlayerState::ATTACK_WITH))) return;
		PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK_WITH);
	}
}


// <---------------------- Attack Combo ---------------------->

void UPlayerAttackComp::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, SkillMaxCombo);

	// Combo UI
	// SetComboAttackUI(SkillKeyIndex_Combo, true);
}

void UPlayerAttackComp::AttackEndState()
{
	// 쿨다운 시작
	if(CurrentSkillInfo && !IsSkillCharging)
		StartCooldown(CurrentSkillInfo->CooldownTimerHandle, CurrentSkillInfo->SkillData->SkillCoolTime);
	// MP가 꽉 찼다면
	if(PlayerStat->GetMP() >= PlayerMaxMP && CurrentSkillInfo != AutoSkill)
	{
		// MP가 꽉 찼다면 열 게이지 관련 설명
		// if(GI) GI->ExecuteTutorial(EExplainType::FULL_HIT_GAUGE);
		
		for(int i = 1; i <= SkillCount; i++)
			SetSkillLockUI(i, true);
	}

	// Reset Damage
	RandDamage = 0;

	// Combo
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	CurrentSkillInfo = nullptr;

	// Charging
	IsChargingInputOn = false;
	CanChargingSkill = false;
}

void UPlayerAttackComp::NextAttackCheck()
{
	CanNextCombo = false;
	
	if(IsComboInputOn)
	{
		Player->TurnPlayer();
		AttackStartComboState();
		PlayerAnim->JumpToAttackMontageSection(CurrentCombo);
		PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK_ONLY);
	}
	else
	{
		SetComboAttackUI(SkillKeyIndex_Combo, false);
		SkillKeyIndex_Combo = -1;
		TurnToAttackWithState();
	}
}

void UPlayerAttackComp::SetComboAttackUI(int32 SkillKeyIndex, bool CanCombo)
{
	if(SkillKeyIndex <= 0) return;
	UE_LOG(LogTemp, Log, TEXT("SetComboAttackUI : "));
	if(CanCombo && CurrentCombo >= SkillMaxCombo) return;
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->SetSkillComboUI(SkillKeyIndex, CanCombo);
}

