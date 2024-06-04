// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Common/UseColor.h"
#include "Components/ActorComponent.h"
#include "Interfaces/SkillInterface.h"
#include "PlayerAttackComp.generated.h"

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

	// Combo
	bool CanNextCombo;
	bool IsComboInputOn;
	int32 CurrentCombo;
	
	// CoolTime
	float CooldownRemain;
	bool bIsOnCooldown;
	FTimerHandle CooldownTimerHandle;

	FSkillInfo()
	{
		SkillData = nullptr;
		
		SkillLevel = 1;

		CanNextCombo = false;
		IsComboInputOn = false;
		CurrentCombo = 0;
		
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

	UPROPERTY(EditAnywhere, Category="Flamethrower")
	TSubclassOf<class APlayerSkillFlamethrower> FlamethrowerFactory;

	UPROPERTY()
	class APlayerSkillFlamethrower* Flamethrower;
	
	int32 PlayerMaxMP;
	
	float MPRegenRate;
	float MPRegenTime;
	float CurrentRegenTime;

	int32 CurrentMP = 0;

	UPROPERTY()
	TArray<AActor*> IgnoreAttackActors;

protected:
	void Attack(FSkillInfo* _TempInfo);
	
public:
	virtual void CompleteSkill() override;
	
	void SetSkillUI(int32 SlotIndex, FSkillInfo* PlayerSkillInfo);
	
	void PlayerExecuteAttack(int32 SkillKeyIndex);
	void PlayerQuitSkill(int32 AttackIndex);

	void MeleeSkillAttackJudgementStart();
	void MeleeSkillAttackJudgementEnd();
	void RangedSkillAttackJudgementStart();
	void RangedSkillAttackJudgmentEnd();

	void ExecuteMeleeSkill();
	void ExecuteRangedSkill();
	
	void ExecuteSwapSkill();
	void ExecuteUltSkill();
	
	void StartCooldown(FTimerHandle& CooldownTimerHandle, float _CoolTime);
	float GetCooldownPercent(float RemainingTime, float _SkillCoolTime);
	void SetSkillCoolDownUI();
	
	bool CanUseSkill(FSkillInfo* _TempSkill);
	
	

	// FORCEINLINE class TArray<class UPlayerSkillBase*> GetPlayerSkills() const {return PlayerSkills;}
	FORCEINLINE void SetCurrentColor(EUseColor NewColor) {CurrentSkillColor = NewColor;}

	
	// <---------------------- Skill Use - Color ---------------------->
public:
	void InitCanUseColor();
	void SetColorUseState(EUseColor _Color, bool bCanUse);
	EUseColor FindSkillColor(EUseColor _CurrentColor);

private:
	TMap<EUseColor, bool> CanUseColor;
	TMap<EUseColor, int32> StartIndexColor;

	
	// <---------------------- Skill Use - Quest, Weapon ---------------------->
public:
	void SetSkillUseState(bool bCanUse, ESkillOpenType OpenType);


	// <---------------------- Skill Upgrade ---------------------->
public:
	void GetSkillUpgradePoint(EUseColor _Color, int32 SkillKeyIndex);


	
	// <---------------------- Attack Combo ---------------------->
public:
	void AttackStartComboState(FSkillInfo* _TempSkill);
	void AttackEndComboState(FSkillInfo* _TempSkill);

	void NextAttackCheck();
	
private:

	
	
	// <---------------------- Skill Data ---------------------->
public:
	FSkillInfo* GetSkillInfo( EUseColor _Color, int32 SkillKeyIndex );
	void SetSkillData(FPlayerSkillData* _SkillData);
	
	FORCEINLINE EUseColor GetCurrentSkillColor() const {return CurrentSkillColor;}

	FORCEINLINE virtual int32 GetSkillLevel() const {return SkillLevel;}
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
	
	UPROPERTY()
	UAnimMontage* SkillMontage;

	int32 SkillLevel; //
	int32 SkillDamage; //
	FVector SkillRange; //
	 
};
