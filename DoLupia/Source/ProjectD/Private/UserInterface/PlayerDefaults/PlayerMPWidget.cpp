// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerMPWidget::SetMPBar(int32 _MP, int32 _MaxMP)
{
	//MPBar->SetPercent(static_cast<float>(_MP) / _MaxMP);
	TargetPercent = static_cast<float>(_MP) / _MaxMP;

	// 시작 시점에 CurrentPercent를 초기화
	if (!GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		CurrentPercent = MPBar->GetPercent();
	}

	StartUpdateTimer();
}

void UPlayerMPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentPercent = 1.0f;
	TargetPercent = 1.0f;
	LerpSpeed = 0.05f;
}

void UPlayerMPWidget::UpdateMPBar()
{
	CurrentPercent = FMath::Lerp( CurrentPercent , TargetPercent , LerpSpeed );

	if (MPBar)
	{
		MPBar->SetPercent( CurrentPercent );
	}

	if (FMath::IsNearlyEqual( CurrentPercent , TargetPercent , 0.01f ))
	{
		StopUpdateTimer();
	}
}

void UPlayerMPWidget::StartUpdateTimer()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		GetWorld()->GetTimerManager().SetTimer( UpdateTimerHandle , this , &UPlayerMPWidget::UpdateMPBar , 0.01f , true );
	}
}

void UPlayerMPWidget::StopUpdateTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		GetWorld()->GetTimerManager().ClearTimer( UpdateTimerHandle );
	}
}
