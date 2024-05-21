// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerMPWidget::SetMPBar(int32 _MP, int32 _MaxMP)
{
	MPBar->SetPercent(static_cast<float>(_MP) / _MaxMP);
}
