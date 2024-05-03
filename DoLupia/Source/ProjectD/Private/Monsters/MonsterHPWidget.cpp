// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterHPWidget.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h"

void UMonsterHPWidget::NativeConstruct()
{
	SetHP( 1 , 1 );
}


void UMonsterHPWidget::SetHP( int32 hp , int32 maxHP )
{
	MonsterHPBar->SetPercent( (float)hp / maxHP );
}
