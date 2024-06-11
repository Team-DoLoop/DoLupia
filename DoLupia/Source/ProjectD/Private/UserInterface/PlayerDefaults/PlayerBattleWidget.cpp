// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"

#include "ProjectDGameInstance.h"
#include "Common/UseColor.h"
#include "Components/ProgressBar.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"
#include "UserInterface/Skill/PlayerSkillSlotWidget.h"
#include "UserInterface/Skill/PlayerSkillWidget.h"

void UPlayerBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UPlayerBattleWidget::StartChargingSkill()
{
	ChargingSkillBar->SetVisibility(ESlateVisibility::Visible);
	ChargingSkillBar->SetFillColorAndOpacity(FLinearColor( 0.38f, 0.52f, 1.0f, 1.0f));
	// PlayAnimation(ChargingAnim);
}

void UPlayerBattleWidget::UpdateChargingSkill(float ChargingTime, bool CanNextAttack)
{
	if(CanNextAttack) ChargingSkillBar->SetFillColorAndOpacity(FLinearColor::Blue);
	ChargingSkillBar->SetPercent(ChargingTime);
}

void UPlayerBattleWidget::EndChargingSkill()
{
	UE_LOG(LogTemp, Log, TEXT("EndChargingSkill Hidden UI"));
	ChargingSkillBar->SetVisibility(ESlateVisibility::Hidden);
}
