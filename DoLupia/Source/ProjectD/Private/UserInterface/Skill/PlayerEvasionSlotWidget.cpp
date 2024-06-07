// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerEvasionSlotWidget.h"

#include "Components/ProgressBar.h"

void UPlayerEvasionSlotWidget::UpdateEvasionCoolTimeUI(float CoolTime)
{
	CoolTimeBar->SetPercent(CoolTime);
}
