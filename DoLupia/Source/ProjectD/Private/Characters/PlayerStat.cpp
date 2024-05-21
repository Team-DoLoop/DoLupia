// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStat.h"

#include "Items/ItemBase.h"


APlayerStat::APlayerStat()
	:	MaxHP(100),CurrentHP(MaxHP),
		MaxMP(100), CurrentMP(MaxMP), MPRegenRate(5.0f), MPRegenTime(1.0f),
		ATK(10.0f),
		DEF(5.0f),
		SkillPoint(0)
{
}

void APlayerStat::initPlayerData()
{
	SetPlayerName(TEXT("Player"));
	
	MaxHP = 100;
	CurrentHP = MaxHP;

	MaxMP = 100;
	CurrentMP = MaxMP;
	MPRegenRate = 5.0f;
	MPRegenTime = 1.0f;

	ATK = 10.0f;
	DEF = 5.0f;

	SkillPoint = 0;
}

void APlayerStat::ChangeStatsItem( UItemBase* CurrentItemBase , UItemBase* NextItemBase )
{
	if(CurrentItemBase)
	{
		ATK -= CurrentItemBase->GetItemStatistics().DamageValue;
		DEF -= CurrentItemBase->GetItemStatistics().ArmorRating;
	}

	if(NextItemBase)
	{
		ATK += NextItemBase->GetItemStatistics().DamageValue;
		DEF += NextItemBase->GetItemStatistics().ArmorRating;
	}
}


// <---------------- MP & HP ---------------->
void APlayerStat::SetHP(int32 _HP)
{
	// int32 NewHP = CurrentHP + _HP;

	if(_HP > MaxHP)
		_HP = MaxHP;

	CurrentHP = _HP;
}

void APlayerStat::SetMP(int32 _MP)
{
	if (_MP > MaxHP)
		_MP = MaxHP;

	CurrentMP = _MP;
}

void APlayerStat::SetMPRegenRate(float _MPRegenRate)
{
	MPRegenRate = _MPRegenRate;
}

void APlayerStat::SetMPRegenTime(float _MPRegenTime)
{
	MPRegenTime = _MPRegenTime;
}

