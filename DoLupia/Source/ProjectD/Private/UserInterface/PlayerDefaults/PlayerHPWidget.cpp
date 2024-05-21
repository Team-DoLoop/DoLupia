// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerHPWidget::SetHPBar(float _HP)
{
	HPBar->SetPercent(_HP);
}
