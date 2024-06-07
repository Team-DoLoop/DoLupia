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
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Skill/PlayerSkillFlamethrower.h"
#include "Characters/Skill/PlayerSkillShield.h"
#include "Characters/Skill/PlayerSkillUlt.h"
#include "Data/PlayerSkillDataStructs.h"
#include "GameFramework/GameSession.h"
#include "Items/Sword/SwordBase.h"
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
	
	IgnoreAttackActors.AddUnique(Player);

	// Add Red W
	if (FlamethrowerFactory)
	{
		Flamethrower = GetWorld()->SpawnActor<APlayerSkillFlamethrower>(FlamethrowerFactory);
		if (Flamethrower)
		{
			Flamethrower->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("WeaponSocket"));
			Flamethrower->SetOwner(Player);
		}
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
	CurrentMP = PlayerStat->GetMP();
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

	for(int i = 1; i <= SkillCount; i++)
	{
		SetSkillUI(i-1, CurrentSkillData[i]);
	}
}

// <---------------------- Attack ---------------------->

void UPlayerAttackComp::Attack(FSkillInfo* _TempInfo)
{

}

void UPlayerAttackComp::FirstAttack(FSkillInfo* _TempInfo, int32 SkillKeyIndex)
{
	if(SkillKeyIndex != 3) CurrentSkillInfo = _TempInfo;
	SetSkillData(_TempInfo);
	SetSpawnLocation();
	
	// UI
	SkillKeyIndex_Combo = SkillKeyIndex;
	
	AttackStartComboState();
	SetSpawnLocation();
	
	Player->TurnPlayer();
	
	// 공격 애니메이션 실행
	PlayerAnim->PlayAttackAnimation(SkillMontage);
	PlayerAnim->JumpToAttackMontageSection(CurrentCombo); // CurrentCombo = 1
	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK_ONLY);
	
	// MP 소모
	CurrentMP = PlayerStat->GetMP() + _TempInfo->SkillData->SkillCost;
	PlayerStat->SetMP(CurrentMP);
	Player->GetPlayerBattleWidget()->GetPlayerMPBar()->SetMPBar(CurrentMP , PlayerMaxMP);
}

void UPlayerAttackComp::CompleteSkill()
{
	if (!PlayerFSMComp) return;
	PlayerFSMComp->ChangePlayerState(EPlayerState::IDLE);
	IgnoreAttackActors.Empty();
	IgnoreAttackActors.AddUnique(Player);
	
	SetComboAttackUI(SkillKeyIndex_Combo, false);
	SkillKeyIndex_Combo = -1;
	
	AttackEndComboState();

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
	
	if(TempSkill && CanUseSkill(TempSkill))
	{
		// 첫 공격이라면 바로 실행
		if (CurrentState != EPlayerState::ATTACK_ONLY && CurrentState != EPlayerState::ATTACK_WITH)
		{
			UE_LOG(LogTemp, Log, TEXT("First Combo Attack"));
			FirstAttack(TempSkill, SkillKeyIndex);
		}
		// 첫 공격이 아니고 콤보 구간이라면
		else if(CurrentState == EPlayerState::ATTACK_ONLY)
		{
			UE_LOG(LogTemp, Log, TEXT("In Combo State Press"));
			// 만약 콤보 가능 구간이라면
			if(CanNextCombo)
			{
				// 콤보 공격 입력
				UE_LOG(LogTemp, Log, TEXT("IsComboInputOn = true"));
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
}

void UPlayerAttackComp::PlayerQuitSkill(int32 AttackIndex)
{
	// W End
	if(AttackIndex == 2)
	{
		if(CurrentSkillColor == EUseColor::RED && Flamethrower) Flamethrower->StopFiring();
	}
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
	DrawDebugBox(GetWorld(), BoxPos, SkillRange, BoxRot, FColor::Red, false, 3.0f);

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
				UE_LOG(LogTemp, Log, TEXT("Melee Attack %s Monster : %d"), *Monster->GetName(), SkillDamage * SkillLevel);
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
}

void UPlayerAttackComp::RangedSkillAttackJudgmentEnd()
{
}


// <------------------------------ Skill Shield ------------------------------>

void UPlayerAttackComp::ShieldSkillStart()
{
	if(!PlayerShieldFactory) return;

	FVector PlayerLoc = Player->GetActorLocation();
	PlayerLoc.Z = PlayerLoc.Z + 30.0f;
	PlayerShield = GetWorld()->SpawnActor<APlayerSkillShield>(PlayerShieldFactory, PlayerLoc, FRotator(0));
	PlayerShield->SetActorScale3D(FVector(0.7f));
	PlayerShield->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	GetWorld()->GetTimerManager().SetTimer(ShieldTimerHandle, this, &UPlayerAttackComp::ShieldSkillEnd, ShieldTime, false);
}

void UPlayerAttackComp::ShieldSkillEnd()
{
	if(!PlayerShield) return;
	
	GetWorld()->GetTimerManager().ClearTimer(ShieldTimerHandle);
	PlayerShield->Destroy();
}


// <------------------------------ Skill Swap ------------------------------>

void UPlayerAttackComp::ExecuteSwapSkill()
{
	// 그 전에 눌렀던 스킬 쿨다운 시작
	if(CurrentSkillInfo)
	{
		AttackEndComboState();
	}
	SetComboAttackUI(SkillKeyIndex_Combo, false);
	
	CurrentSkillColor = FindSkillColor(CurrentSkillColor);
	for(int i = 0; i < 2; i++)
	{
		FSkillInfo* _TempSkill = GetSkillInfo(CurrentSkillColor, i+1);
		SetSkillUI(i, _TempSkill);
	}
	
	SetSkillCoolDownUI();
}

void UPlayerAttackComp::SetSkillUI(int32 SlotIndex, FSkillInfo* PlayerSkillInfo)
{
	if (!Player) return;
	
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpdateSkillUI(SlotIndex, PlayerSkillInfo);
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


// <------------------------------ Skill Data ------------------------------>

FSkillInfo* UPlayerAttackComp::GetSkillInfo( EUseColor _Color, int32 SkillKeyIndex)
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
	SkillDamage = _SkillData->SkillDamage;
	SkillRange = _SkillData->SkillRange;
	SkillMaxCombo = _SkillData->SkillMaxCombo;
	SkillLevel = _TempInfo->SkillLevel;
}

void UPlayerAttackComp::SetSpawnLocation()
{
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (!bHitSuccessful) return;

	FVector MouseLocation = Hit.Location;
	FVector PlayerLoc = Player->GetActorLocation();
	float Distance = FVector::Dist(PlayerLoc, MouseLocation);
	
	if (Distance > MaxUltRange)
	{
		FVector Direction = (MouseLocation - PlayerLoc).GetSafeNormal();
		SpawnLocation = PlayerLoc + Direction * MaxUltRange;
	}
	else  SpawnLocation = MouseLocation;
}


// <---------------------- Skill Upgrade ---------------------->

void UPlayerAttackComp::GetSkillUpgradePoint(EUseColor _Color, int32 SkillKeyIndex)
{
	FSkillInfo* _TempSkill = GetSkillInfo(_Color, SkillKeyIndex);
		
	if(_TempSkill)
	{
		if(_TempSkill->SkillLevel < 5)
			_TempSkill->SkillLevel = _TempSkill->SkillLevel + 1;
		
		// UI 업데이트
		Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerSkillUI()->UpgradeSkillLevelUI(SkillKeyIndex-1, _TempSkill->SkillLevel);
		UE_LOG(LogTemp,Log,TEXT("Get GetSkillUpgradePoint"));
	}
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
		return 1.0f - (RemainingTime / _SkillCoolTime);
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
	if(CurrentMP >= PlayerMaxMP) return false;
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
	SetComboAttackUI(SkillKeyIndex_Combo, true);
}

void UPlayerAttackComp::AttackEndComboState()
{
	// 쿨다운 시작
	if(CurrentSkillInfo)
		StartCooldown(CurrentSkillInfo->CooldownTimerHandle, CurrentSkillInfo->SkillData->SkillCoolTime);
	
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	CurrentSkillInfo = nullptr;
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

