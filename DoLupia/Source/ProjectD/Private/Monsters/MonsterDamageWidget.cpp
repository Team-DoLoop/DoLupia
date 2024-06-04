// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterDamageWidget.h"

#include "Components/TextBlock.h"

void UMonsterDamageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UMonsterDamageWidget::SetDamage( int32 damage )
{
	DamageText->SetText( FText::AsNumber( damage ) );
	PlayAnimationForward( anim , 1 , false );
}

