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

public:
	void initPlayerData();

	void ChangeStatsItem(UItemBase* CurrentItemBase, UItemBase* NextItemBase );

	FORCEINLINE int32 GetHP() const { return CurrentHP; }
	FORCEINLINE void  SetHP(int32 _HP)
	{
		// int32 NewHP = CurrentHP + _HP;

		if(_HP > MaxHP)
			_HP = MaxHP;

		CurrentHP = _HP;
	}
	
	FORCEINLINE int32 GetMP() const {return CurrentMP;}
	FORCEINLINE void  SetMP( int32 _MP )
	{
		if (_MP > MaxHP)
			_MP = MaxHP;

		CurrentHP = _MP;
	}
	
	FORCEINLINE int32 GetATK() const {return ATK;}
	FORCEINLINE void  SetATK(float _ATK) {ATK = _ATK;}
	
	FORCEINLINE int32 GetDEF() const {return DEF;}
	FORCEINLINE void  SetDEF(float _DEF) {DEF = _DEF;}


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
};
