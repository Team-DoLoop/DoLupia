// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossHPWidget.h"
#include "Components/ProgressBar.h"

void UBossHPWidget::NativeConstruct()
{
	SetHP( 1 , 1 );
}

void UBossHPWidget::SetHP( int32 hp , int32 maxHP )
{
	BossHPBar->SetPercent( (float)hp / maxHP );
}



