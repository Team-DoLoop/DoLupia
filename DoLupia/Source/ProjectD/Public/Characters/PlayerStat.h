// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStat.generated.h"

/**
 * 
 */

class UItemBase;

UCLASS()
class PROJECTD_API APlayerStat : public APlayerState
{
	GENERATED_BODY()

	APlayerStat();

	// <---------------------- Player ---------------------->
private:	

public:
	void initPlayerData();


	
	// <---------------------- HP ---------------------->
private:
	UPROPERTY( EditAnywhere )
	int32 MaxHP;

	UPROPERTY( VisibleAnywhere )
	int32 CurrentHP;

public:
	FORCEINLINE int32 GetMaxHP() const { return MaxHP; }
	FORCEINLINE int32 GetHP() const { return CurrentHP; }
	void  SetHP(int32 _HP);

	
	// <---------------------- MP ---------------------->
private:
	UPROPERTY( EditAnywhere )
	int32 MaxMP;

	UPROPERTY( VisibleAnywhere )
	int32 CurrentMP;
	
	UPROPERTY(EditAnywhere)
	float MPRegenRate;

	UPROPERTY(EditAnywhere)
	float MPRegenTime;

public:
	FORCEINLINE int32 GetMaxMP() const { return MaxMP; }
	FORCEINLINE int32 GetMP() const {return CurrentMP;}
	FORCEINLINE float GetMPRegenRate() const {return MPRegenRate;}
	FORCEINLINE float GetMPRegenTime() const {return MPRegenTime;}
	
	void SetMP( int32 _MP );
	void SetMPRegenRate(float _MPRegenRate);
	void SetMPRegenTime(float _MPRegenTime);


	
	// <---------------------- ATK ---------------------->
private:
	UPROPERTY( VisibleAnywhere )
	float ATK;
	
public:
	FORCEINLINE int32 GetATK() const {return ATK;}
	FORCEINLINE void  SetATK(float _ATK) {ATK = _ATK;}

	
	// <---------------------- DEF ---------------------->
private:
	UPROPERTY( VisibleAnywhere )
	float DEF;

public:
	FORCEINLINE int32 GetDEF() const {return DEF;}
	FORCEINLINE void  SetDEF(float _DEF) {DEF = _DEF;}

	

	// <---------------------- SkillPoint ---------------------->
private:
	UPROPERTY( VisibleAnywhere )
	int32 SkillLevelMelee;

	UPROPERTY( VisibleAnywhere )
	int32 SkillLevelRange;

	
public:
	void AddSkillLevelMelee( int32 SkillPoint );
	void AddSkillLevelRange( int32 SkillPoint );
	

	// <---------------------- Item ---------------------->
private:

public:
	void ChangeStatsItem(UItemBase* CurrentItemBase, UItemBase* NextItemBase );

};
