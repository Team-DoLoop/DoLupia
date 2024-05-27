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
		PlayerSkillSlotArray.Add(PlayerSkillSlot);
		PlayerSkillSlot->SetUI(GI->GetPlayerSkillData(i));
		
		if(UHorizontalBoxSlot* SkillSlot = SkillBox->AddChildToHorizontalBox(PlayerSkillSlot))
		{
			SkillSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
			SkillSlot->SetHorizontalAlignment(HAlign_Fill);
			SkillSlot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}

void UPlayerSkillWidget::UpdateSkillUI(FPlayerSkillData* PlayerSkillData)
{
	for(int i = 0; i < 2; i++)
	{
		PlayerSkillSlotArray[i]->SetUI(PlayerSkillData);
	}
}
