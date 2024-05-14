// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStat.h"


APlayerStat::APlayerStat()
	:	MaxHP(100.0f), MaxMP(100.0f),
		CurrentHP(MaxHP), CurrentMP(MaxMP),
		ATK(10.0f),
		DEF(5.0f)
{
}

void APlayerStat::initPlayerData()
{
	SetPlayerName(TEXT("Player"));
	MaxHP = 100;
	MaxMP = 100;
	CurrentHP = MaxHP;
	CurrentMP = MaxMP;
	ATK = 10.0f;
	DEF = 5.0f;
}
