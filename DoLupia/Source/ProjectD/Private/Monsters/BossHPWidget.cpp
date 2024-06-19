// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossHPWidget.h"
#include "Components/ProgressBar.h"

void UBossHPWidget::NativeConstruct()
{
	SetHP( 1 , 1 );
}

void UBossHPWidget::SetHP(int32 hp, int32 maxHP)
{
	TargetHP = hp;
	MaxHP = maxHP;
	BossHPBar->SetPercent( (float)hp / maxHP );
	GetWorld()->GetTimerManager().SetTimer( InterpolationTimerHandle , this , &UBossHPWidget::UpdateHPBar , 0.02f , true );

	// 현재 HP를 HP 바의 백분율로 설정
	CurrentHP = BossHPBar->Percent * MaxHP;
}

void UBossHPWidget::UpdateHPBar()
{
	CurrentHP = FMath::FInterpTo( CurrentHP , TargetHP , GetWorld()->GetDeltaSeconds() , 5.0f ); // 5.0은 보간 속도

	// 프로그레스 바 업데이트
	BossHPBar->SetPercent( CurrentHP / MaxHP );

	// 목표 HP에 도달하면 타이머 종료
	if (FMath::IsNearlyEqual( CurrentHP , TargetHP , 0.01f ))
	{
		GetWorld()->GetTimerManager().ClearTimer( InterpolationTimerHandle );
	}
}
