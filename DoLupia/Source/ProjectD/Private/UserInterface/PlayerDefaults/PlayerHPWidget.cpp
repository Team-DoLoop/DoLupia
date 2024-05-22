// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerHPWidget::SetHPBar(int32 _HP, int32 _MaxHP)
{
	HPBar->SetPercent(static_cast<float>(_HP) / _MaxHP);
}
