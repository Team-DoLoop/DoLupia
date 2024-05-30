// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillSlotWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Data/PlayerSkillDataStructs.h"

void UPlayerSkillSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPlayerSkillSlotWidget::InitUI()
{
}

void UPlayerSkillSlotWidget::SetUI(FPlayerSkillData* PlayerSkillData)
{
	if(PlayerSkillData && PlayerSkillData->SkillThumnail)
	{
		SkillThumnail->SetBrushFromTexture(PlayerSkillData->SkillThumnail);
	}
}

void UPlayerSkillSlotWidget::SetCoolTimeBar(float CoolTime)
{
	CoolTimeBar->SetPercent(CoolTime);
}


