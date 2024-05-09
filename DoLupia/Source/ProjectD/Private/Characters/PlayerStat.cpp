// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStat.h"

APlayerStat::APlayerStat()
{
	HP = 100;
	MP = 100;
	ATK = 100;
	DEF = 100;
}

void APlayerStat::initPlayerData()
{
	SetPlayerName(TEXT("Player"));
	HP = 100;
	MP = 100;
	ATK = 100;
	DEF = 100;
}
