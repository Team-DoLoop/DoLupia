// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Common/UseColor.h"
#include "Components/ActorComponent.h"
#include "Interfaces/SkillInterface.h"
#include "PlayerAttackComp.generated.h"

USTRUCT()
struct FSkillInfo
{
	GENERATED_BODY()

	float CooldownTime;
	float CooldownRemain;
	bool bIsOnCooldown;
	FTimerHandle CooldownTimerHandle;

	FSkillInfo()
	{
		CooldownTime = 0.0f;
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
	UPROPERTY(EditAnywhere, Category = "Skill")
	TArray<FSkillInfo> Skills;
	
	int32 PlayerMaxMP;
	
	float MPRegenRate;
	float MPRegenTime;
	float CurrentRegenTime;
	int PlayerAttackStatus = 0;

	int32 CurrentMP = 0;

	UPROPERTY()
	TArray<AActor*> IgnoreAttackActors;
	
	UPROPERTY()
	class UAnimMontage* AutoAttackMontage;

protected:
	void Attack();
	
public:
	virtual void CancelSkill() override;
	virtual void ReadySkill() override;
	virtual void CompleteSkill() override;
	
	void SetSkillCoolDownUI(int32 SlotIndex, float CoolTime);
	void SetSkillUI(int32 SlotIndex, FPlayerSkillData* PlayerSkillData);
	
	void PlayerExecuteAttack(int32 AttackIndex);
	void MeleeSkillAttackJudgementStart();
	void MeleeSkillAttackJudgementEnd();

	void MeleeSkill();
	void RangedSkill();
	void SwapSkill();
	void UltSkill();

	void UpdateCooldown(int32 AttackIndex);
	void ResetCooldown(int32 AttackIndex);
	bool CanUseSkill(int32 AttackIndex);
	
	UFUNCTION()
	float GetCooldownPercent(int32 AttackIndex);
	

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
	
	// <---------------------- Skill Use - Weapon ---------------------->
public:
	void SetSkillUseState(bool bCanUse);
	
	
	
	// <---------------------- Skill Data ---------------------->
public:
	void SetSkillAttackData( FPlayerSkillData* PlayerSkillData );
	//void CheckNextColor();
	FORCEINLINE EUseColor GetCurrentSkillColor() const {return CurrentSkillColor;}
	
	FORCEINLINE virtual FString GetSkillName() const {return SkillName;}
	FORCEINLINE virtual int32 GetSkillLevel() const {return SkillLevel;}
	FORCEINLINE virtual int32 GetSkillCost() const {return SkillCost;}
	FORCEINLINE virtual int32 GetSkillCoolTime() const {return SkillCoolTime;}
	FORCEINLINE virtual int32 GetSkillDamage() const {return SkillDamage;}

	
private:
	TArray<FPlayerSkillData*> CurrentSkillData;
	EUseColor CurrentSkillColor = EUseColor::NONE; // X, 빨, 노, 파

	int32 SkillCount = 4;						// 플레이어 스킬 개수
	
	int32 SkillID;
	EUseColor SkillColor;
	ESkillType SkillType;
	FString SkillName;

	UPROPERTY()
	UTexture2D* SkillThumnail;
	UPROPERTY()
	UAnimMontage* SkillMontage;
	
	FText SkillDescription;
	int32 SkillLevel; //
	int32 SkillCost; //
	int32 SkillCoolTime; //
	int32 SkillDamage; //
	FVector SkillRange; //
	 
};
