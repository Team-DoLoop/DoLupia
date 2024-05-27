// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillWidget.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "UserInterface/Skill/PlayerSkillSlotWidget.h"

void UPlayerSkillWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitSkillSlot();
}

void UPlayerSkillWidget::InitSkillSlot()
{

}
