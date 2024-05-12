// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerStat.h"


APlayerStat::APlayerStat()
	: HP(100.0f),
	  MP(100.0f),
	  ATK(10.0f),
	  DEF(5.0f)
{
}

void APlayerStat::initPlayerData()
{
	SetPlayerName(TEXT("Player"));
	HP = 100;
	MP = 100;
	ATK = 10.0f;
	DEF = 5.0f;
}
