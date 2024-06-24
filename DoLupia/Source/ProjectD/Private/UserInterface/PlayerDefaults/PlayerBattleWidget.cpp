// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"

#include "Components/ProgressBar.h"
#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"

void UPlayerBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UPlayerBattleWidget::StartChargingSkill()
{
	ChargingSkillBar->SetVisibility(ESlateVisibility::Visible);
	ChargingSkillBar->SetFillColorAndOpacity(FLinearColor(167.0f / 255, 230.0f / 255, 255.0f / 255, 1.0f));
	// PlayAnimation(ChargingAnim);
}

void UPlayerBattleWidget::UpdateChargingSkill(float ChargingTime, bool CanNextAttack)
{
	if(CanNextAttack) ChargingSkillBar->SetFillColorAndOpacity(FLinearColor(53.0f/255, 114.0f/255, 239.0f/255, 1.0f));
	ChargingSkillBar->SetPercent(ChargingTime);
}

void UPlayerBattleWidget::EndChargingSkill()
{
	UE_LOG(LogTemp, Log, TEXT("EndChargingSkill Hidden UI"));
	ChargingSkillBar->SetVisibility(ESlateVisibility::Hidden);
}
