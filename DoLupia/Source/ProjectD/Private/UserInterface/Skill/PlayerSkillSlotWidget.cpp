// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillSlotWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Data/PlayerSkillDataStructs.h"

void UPlayerSkillSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ProgressBarColor.Add(EUseColor::NONE, FLinearColor( 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::RED, FLinearColor(1.0f, 0.0f, 0.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::YELLOW, FLinearColor(1.0f, 1.0f, 0.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::BLUE, FLinearColor(0.0f, 0.0f, 1.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::COLOR, FLinearColor( 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.5f));

}

void UPlayerSkillSlotWidget::InitUI()
{
}

void UPlayerSkillSlotWidget::SetUI(FPlayerSkillData* PlayerSkillData)
{
	if(PlayerSkillData && PlayerSkillData->SkillThumnail)
	{
		CoolTimeBar->SetFillColorAndOpacity(ProgressBarColor[PlayerSkillData->SkillColor]);
		SkillThumnail->SetBrushFromTexture(PlayerSkillData->SkillThumnail);
	}
}

void UPlayerSkillSlotWidget::SetCoolTimeBar(float CoolTime)
{
	CoolTimeBar->SetPercent(CoolTime);
}


