﻿// Fill out your copyright notice in the Description page of Project Settings.

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

private:
	UPROPERTY( VisibleAnywhere )
	int32 MaxHP;

	UPROPERTY( VisibleAnywhere )
	int32 CurrentHP;

	UPROPERTY( VisibleAnywhere )
	int32 MaxMP;

	UPROPERTY( VisibleAnywhere )
	int32 CurrentMP;

	UPROPERTY( VisibleAnywhere )
	float ATK;

	UPROPERTY( VisibleAnywhere )
	float DEF;

	UPROPERTY( VisibleAnywhere )
	int32 SkillPoint;


public:
	void initPlayerData();

	void ChangeStatsItem(UItemBase* CurrentItemBase, UItemBase* NextItemBase );

	FORCEINLINE int32 GetMaxHP() const { return MaxHP; }
	FORCEINLINE int32 GetMaxMP() const { return MaxMP; }
	
	FORCEINLINE int32 GetHP() const { return CurrentHP; }
	void  SetHP(int32 _HP);
	
	FORCEINLINE int32 GetMP() const {return CurrentMP;}
	void  SetMP( int32 _MP );
	
	FORCEINLINE int32 GetATK() const {return ATK;}
	FORCEINLINE void  SetATK(float _ATK) {ATK = _ATK;}
	
	FORCEINLINE int32 GetDEF() const {return DEF;}
	FORCEINLINE void  SetDEF(float _DEF) {DEF = _DEF;}

	FORCEINLINE int32 GetSkillPoint() const {return SkillPoint;}
	FORCEINLINE void  SetSkillPoint(float _SkillPoint) {SkillPoint = _SkillPoint;}

};
