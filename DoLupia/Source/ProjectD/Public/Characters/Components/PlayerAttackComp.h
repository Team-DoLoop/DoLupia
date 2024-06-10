// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Common/UseColor.h"
#include "Components/ActorComponent.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Interfaces/SkillInterface.h"
#include "PlayerAttackComp.generated.h"

class APlayerSkillLightning;
class APlayerSkillUlt;
class APlayerSkillShield;
class APlayerSkillElecBlast;
struct FPlayerSkillData;

UENUM(BlueprintType)
enum ESkillOpenType : int8
{
	NONE UMETA(DisplayName = "None"),
	QUEST UMETA(DisplayName = "Quest"),
	WEAPON UMETA(DisplayName = "Weapon"),
};

USTRUCT()
struct FSkillInfo
{
	GENERATED_BODY()
	
	FPlayerSkillData* SkillData;

	int32 SkillLevel;
	
	// CoolTime
	float CooldownRemain;
	bool bIsOnCooldown;
	FTimerHandle CooldownTimerHandle;

	FSkillInfo()
	{
		SkillData = nullptr;
		
		SkillLevel = 1;
		
		CooldownRemain = 0.0f;
		bIsOnCooldown = false;
	}
};

struct FPlayerSkillData;
enum class ESkillType : uint8;
class UProjectDGameInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerAttackComp : public UActorComponent, public ISkillInterface
{
	GENERATED_BODY()
	
	friend class AProjectDPlayerController;
	
public:	
	// Sets default values for this component's properties
	UPlayerAttackComp();

private:
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// <---------------------- Game ---------------------->
private:
	UProjectDGameInstance* GI;

	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;
	
	UPROPERTY()
	class UPlayerFSMComp* PlayerFSMComp;

	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY()
	class APlayerStat* PlayerStat;

	
public:
	
	
	
	// <---------------------- Attack ---------------------->
private:
	int32 PlayerMaxMP;

	/*
	float MPRegenRate;
	float MPRegenTime;
	float CurrentRegenTime;
	*/

	int32 CurrentMP = 0;

	UPROPERTY()
	TArray<AActor*> IgnoreAttackActors;

	UPROPERTY(EditAnywhere)
	USoundWave* CantAttackSoundWave;

protected:
	void Attack(FSkillInfo* _TempInfo);
	void FirstAttack(FSkillInfo* _TempInfo, int32 SkillKeyIndex);
	
public:
	virtual void CompleteSkill() override;
	void AttackEndState();
	
	void SetSkillUI(int32 SlotIndex, FSkillInfo* PlayerSkillInfo);
	
	void PlayerExecuteAttack(int32 SkillKeyIndex);
	void PlayerQuitSkill(int32 AttackIndex);
	
	bool CanUseSkill(FSkillInfo* _TempSkill);
	void TurnToAttackWithState();

	
	// <---------------------- Melee Attack ---------------------->
public:
	void MeleeSkillAttackJudgementStart();
	void MeleeSkillAttackJudgementEnd();

	
	// <---------------------- Ranged Attack ---------------------->
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerSkillElecBlast> PlayerElecBlastFactory;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerSkillLightning> PlayerLightningFactory;
	
	void RangedSkillAttackJudgementStart();
	void RangedSkillAttackJudgmentEnd();

private :
	UPROPERTY()
	APlayerSkillElecBlast* PlayerElecBlast;

	UPROPERTY()
	APlayerSkillLightning* PlayerLightning;
	

	
	// <---------------------- Shield Skill ---------------------->
public:
	void ShieldSkillStart();
	void ShieldSkillEnd();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerSkillShield> PlayerShieldFactory;

private :
	FTimerHandle ShieldTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Shield")
	float ShieldTime = 6.0f;

	UPROPERTY()
	APlayerSkillShield* PlayerShield;

	

	// <---------------------- Swap Skill ---------------------->
public:
	void ExecuteSwapSkill();

private:
	UPROPERTY(EditAnywhere)
	USoundWave* SwapSoundWave;

	
	// <---------------------- Ult Skill ---------------------->
public:
	void ExecuteUltSkill();
	void ExecuteUltEnd();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerSkillUlt> PlayerUltFactory;

private:
	FTimerHandle UltTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Ult")
	float UltTime = 3.0f;

	UPROPERTY()
	APlayerSkillUlt* PlayerUlt;


	// <---------------------- Skill CoolDown ---------------------->
public:
	void StartCooldown(FTimerHandle& CooldownTimerHandle, float _CoolTime);
	float GetCooldownPercent(float RemainingTime, float _SkillCoolTime);
	void SetSkillCoolDownUI();
	

	// FORCEINLINE class TArray<class UPlayerSkillBase*> GetPlayerSkills() const {return PlayerSkills;}
	FORCEINLINE void SetCurrentColor(EUseColor NewColor) {CurrentSkillColor = NewColor;}

	
	// <---------------------- Skill Use - Color ---------------------->
public:
	void InitCanUseColor();
	void SetColorUseState(EUseColor _Color, bool bCanUse);
	EUseColor FindSkillColor(EUseColor _CurrentColor);

private:
	TMap<EUseColor, bool> CanUseColor;
	// TMap<EUseColor, int32> StartIndexColor;

	
	// <---------------------- Skill Use - Quest, Weapon ---------------------->
public:
	void InitSkillUI();
	void SetSkillUseState(bool bCanUse, ESkillOpenType OpenType);
	void SetSkillLockUI(int32 SkillKeyIndex, bool IsSkillLock);

private:
	bool IsUnLockSwap = false;
	bool IsUnLockUlt = false;


	// <---------------------- Skill Upgrade ---------------------->
public:
	void GetSkillUpgradePoint(EUseColor _Color, int32 SkillKeyIndex);


	
	// <---------------------- Attack Combo ---------------------->
public:
	void AttackStartComboState();

	void NextAttackCheck();

	void SetComboAttackUI(int32 SkillKeyIndex, bool CanCombo);
	
private:
	bool CanNextCombo;
	bool IsComboInputOn;
	int32 CurrentCombo = 0;
	int32 SkillKeyIndex_Combo = -1;


	
	// <---------------------- Charging Skill ---------------------->
public:
	void PlayerChargingSkill();
	void PlayerChargingEndSkill();
	void NextChargingCheck();

private:
	bool IsChargingInputOn;
	bool CanChargingSkill;
	
	
	// <---------------------- Skill Data ---------------------->
public:
	FSkillInfo* GetSkillInfo( EUseColor _Color, int32 SkillKeyIndex );
	void SetSkillData(FSkillInfo* _TempInfo);
	void SetSpawnLocation();
	
	FORCEINLINE EUseColor GetCurrentSkillColor() const {return CurrentSkillColor;}

	FORCEINLINE virtual int32 GetSkillLevel() const {return SkillLevel;}
	FORCEINLINE virtual int32 GetSkillCount() const {return SkillCount;}
	FORCEINLINE virtual int32 GetSkillDamage() const {return SkillDamage;}

	
private:
	FSkillInfo* CurrentSkillInfo;
	
	//TArray<FPlayerSkillData*> CurrentSkillData;
	EUseColor CurrentSkillColor = EUseColor::NONE;	// X, 빨, 노, 파

	TArray<FSkillInfo*> CantSkill;

	FSkillInfo* AutoSkill;
	
	FSkillInfo* RedQSkill;
	FSkillInfo* RedWSkill;
	
	FSkillInfo* YellowQSkill;
	FSkillInfo* YellowWSkill;
	
	FSkillInfo* BlueQSkill;
	FSkillInfo* BlueWSkill;
	
	FSkillInfo* SwapSkill;
	FSkillInfo* UltSkill;
	
	int32 SkillCount = 4;							// 플레이어 스킬 개수
	FVector SpawnLocation;
	
	UPROPERTY()
	UAnimMontage* SkillMontage;

	int32 SkillLevel; //
	int32 SkillDamage; //
	FVector SkillRange; //
	int32 SkillMaxCombo; //
	float SkillMaxRange; //
	bool IsSkillCharging; //

	 
};
