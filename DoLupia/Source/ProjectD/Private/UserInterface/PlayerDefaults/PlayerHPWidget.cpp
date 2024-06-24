// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"

#include "Components/ProgressBar.h"

void UPlayerHPWidget::SetHPBar(int32 _HP, int32 _MaxHP)
{
	//HPBar->SetPercent(static_cast<float>(_HP) / _MaxHP);
	TargetPercent = static_cast<float>(_HP) / _MaxHP;

	// 시작 시점에 CurrentPercent를 초기화
	if (!GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		CurrentPercent = HPBar->GetPercent();;
	}

	StartUpdateTimer();
}

void UPlayerHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentPercent = 1.0f; 
	TargetPercent = 1.0f;
	LerpSpeed = 0.05f;
}

void UPlayerHPWidget::UpdateHPBar()
{
	CurrentPercent = FMath::Lerp( CurrentPercent , TargetPercent , LerpSpeed );

	if (HPBar)
	{
		HPBar->SetPercent( CurrentPercent );
	}

	if (FMath::IsNearlyEqual( CurrentPercent , TargetPercent , 0.01f ))
	{
		StopUpdateTimer();
	}
}

void UPlayerHPWidget::StartUpdateTimer()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		GetWorld()->GetTimerManager().SetTimer( UpdateTimerHandle , this , &UPlayerHPWidget::UpdateHPBar , 0.01f , true );
	}
}

void UPlayerHPWidget::StopUpdateTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive( UpdateTimerHandle ))
	{
		GetWorld()->GetTimerManager().ClearTimer( UpdateTimerHandle );
	}
}
