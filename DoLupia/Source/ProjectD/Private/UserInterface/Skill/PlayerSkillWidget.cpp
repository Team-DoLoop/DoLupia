// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillWidget.h"

#include "ProjectDGameInstance.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/Skill/PlayerSkillSlotWidget.h"

void UPlayerSkillWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(!GI) return;
	InitSkillSlot();
}

void UPlayerSkillWidget::InitSkillSlot()
{
	for(int i = 0; i < 4; i++)
	{
		auto PlayerSkillSlot = CreateWidget<UPlayerSkillSlotWidget>(this, PlayerSkillSlotFactory);
		if(PlayerSkillSlot)
		{
			PlayerSkillSlotArray.Add(PlayerSkillSlot);
			PlayerSkillSlot->SetSkillIndex(i);
			PlayerSkillSlot->SetUI(GI->GetPlayerSkillData(0));	// 모두 스킬 사용 X로 초기화
			
			if(UHorizontalBoxSlot* SkillSlot = SkillBox->AddChildToHorizontalBox(PlayerSkillSlot))
			{
				SkillSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			}
		}
	}
}

// <--------------------- Update Skill Level --------------------->

void UPlayerSkillWidget::UpdateSkillUI(int32 SlotIndex, FSkillInfo* PlayerSkillInfo)
{
	PlayerSkillSlotArray[SlotIndex]->SetUI(PlayerSkillInfo->SkillData);
}

void UPlayerSkillWidget::UpdateSkillCoolTimeUI(int32 SlotIndex, float CoolTime)
{
	PlayerSkillSlotArray[SlotIndex]->SetCoolTimeBar(CoolTime);
}


// <--------------------- Upgrade Skill Level --------------------->

void UPlayerSkillWidget::UpgradeSkillLevelUI(int32 SlotIndex, int32 SkillLevel)
{
	PlayerSkillSlotArray[SlotIndex]->UpgradeSkillSlotLevelUI(SkillLevel);
}
