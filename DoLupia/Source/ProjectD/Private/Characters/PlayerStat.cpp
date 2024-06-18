// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStat.h"
#include "Characters/ProjectDCharacter.h"

#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"
#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"

#include "Items/ItemBase.h"


APlayerStat::APlayerStat()
	:	MaxHP(1000),CurrentHP(MaxHP),
		MaxMP(100), CurrentMP(0), MPRegenRate(5.0f), MPRegenTime(1.0f),
		ATK(10.0f),
		DEF(5.0f),
		SkillLevelMelee(0),
		SkillLevelRange(0)
{
	
}

void APlayerStat::initPlayerData()
{
	SetPlayerName(TEXT("Player"));
	
	MaxHP = 1000;
	CurrentHP = MaxHP;

	MaxMP = 100;
	CurrentMP = 0;
	MPRegenRate = 5.0f;
	MPRegenTime = 1.0f;

	ATK = 1.0f;
	DEF = 5.0f;

	SkillLevelMelee = 0;
	SkillLevelRange = 0;
}

void APlayerStat::AddSkillLevelMelee( int32 SkillPoint )
{
	SkillLevelMelee += SkillPoint;
}

void APlayerStat::AddSkillLevelRange( int32 SkillPoint )
{
	SkillLevelRange += SkillPoint;
}

void APlayerStat::ChangeStatsItem( UItemBase* CurrentItemBase , UItemBase* NextItemBase )
{
	if(CurrentItemBase)
	{
		const FItemStatistics& ItemStatistics = CurrentItemBase->GetItemStatistics();

		ATK -= ItemStatistics.DamageValue;
		DEF -= ItemStatistics.ArmorRating;
		MaxHP -= ItemStatistics.HealthValue;
	}

	if(NextItemBase)
	{
		const FItemStatistics& ItemStatistics = NextItemBase->GetItemStatistics();

		ATK += ItemStatistics.DamageValue;
		DEF += ItemStatistics.ArmorRating;
		MaxHP += ItemStatistics.HealthValue;
	}
}


// <---------------- MP & HP ---------------->
void APlayerStat::SetHP(int32 _HP)
{
	if (CurrentHP != _HP)
	{
		if (_HP > MaxHP)
			_HP = MaxHP;

		CurrentHP = _HP;

		if (AProjectDCharacter* Character = Cast<AProjectDCharacter>( GetOwner() ))
			if(UPlayerBattleWidget* BattleWidget = Character->GetPlayerBattleWidget())
				if(UPlayerHPWidget* HpWidget = BattleWidget->GetPlayerHPBar())
					HpWidget->SetHPBar( CurrentHP , MaxHP );
	}

}

void APlayerStat::SetMP(int32 _MP)
{
	if (CurrentMP != _MP)
	{
		if (_MP > MaxMP)
			_MP = MaxMP;

		if(_MP < 0)
			_MP = 0;

		CurrentMP = _MP;

		if (AProjectDCharacter* Character = Cast<AProjectDCharacter>( GetOwner() ))
			if (UPlayerBattleWidget* BattleWidget = Character->GetPlayerBattleWidget())
				if (UPlayerMPWidget* MpWidget = BattleWidget->GetPlayerMPBar())
					MpWidget->SetMPBar( CurrentMP , MaxMP );
	}
}

void APlayerStat::SetMPRegenRate(float _MPRegenRate)
{
	MPRegenRate = _MPRegenRate;
}

void APlayerStat::SetMPRegenTime(float _MPRegenTime)
{
	MPRegenTime = _MPRegenTime;
}

