// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillWidget.h"

#include "ProjectDGameInstance.h"
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
			PlayerSkillSlot->SetUI(GI->GetPlayerSkillData(0));	// 모두 스킬 사용 X로 초기화
			
			if(UHorizontalBoxSlot* SkillSlot = SkillBox->AddChildToHorizontalBox(PlayerSkillSlot))
			{
				SkillSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			}
		}
	}
}

void UPlayerSkillWidget::UpdateSkillUI(int32 SlotIndex, FPlayerSkillData* PlayerSkillData)
{
	PlayerSkillSlotArray[SlotIndex]->SetUI(PlayerSkillData);
}
