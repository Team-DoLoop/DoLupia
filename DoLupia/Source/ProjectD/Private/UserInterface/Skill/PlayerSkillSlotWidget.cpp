// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerSkillSlotWidget.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Spacer.h"
#include "Data/PlayerSkillDataStructs.h"
#include "Kismet/GameplayStatics.h"

void UPlayerSkillSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	ProgressBarColor.Add(EUseColor::NONE, FLinearColor( 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::RED, FLinearColor(1.0f, 0.0f, 0.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::YELLOW, FLinearColor(1.0f, 1.0f, 0.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::BLUE, FLinearColor(0.0f, 0.0f, 1.0f, 0.5f));
	ProgressBarColor.Add(EUseColor::COLOR, FLinearColor( 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.5f));
	
	InitSkillLevelUI();
}

void UPlayerSkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerSkillSlotWidget::InitUI()
{
	
}

void UPlayerSkillSlotWidget::InitSkillLevelUI()
{
	for(int i = 0; i < 5; i ++)
	{
		// 이미지 추가
		UImage* SkillLevelImage = NewObject<UImage>(this);
		if (SkillLevelImage)
		{
			SkillLevelSlot.Add(SkillLevelImage);
			if(i == 0) 	SkillLevelImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
			else SkillLevelImage->SetColorAndOpacity(FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));
			UHorizontalBoxSlot* ImageSlot = SkillLevelBox-> AddChildToHorizontalBox(SkillLevelImage);
			if (ImageSlot)
			{
				FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
				Size.Value = 0.1f;
				ImageSlot->SetSize(Size);
				ImageSlot->SetHorizontalAlignment(HAlign_Fill);
				ImageSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}

		// 스페이서 추가
		USpacer* Spacer = NewObject<USpacer>(this);
		if (Spacer)
		{
			UHorizontalBoxSlot* SpacerSlot = SkillLevelBox->AddChildToHorizontalBox(Spacer);
			if (SpacerSlot)
			{
				FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
				Size.Value = 0.1f;
				SpacerSlot->SetSize(Size);
				SpacerSlot->SetHorizontalAlignment(HAlign_Fill);
				SpacerSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}
}

void UPlayerSkillSlotWidget::SetUI(FPlayerSkillData* _SkillData)
{
	if(_SkillData && _SkillData->SkillThumnail)
	{
		SkillThumnail->SetColorAndOpacity(ProgressBarColor[_SkillData->SkillColor]);
		
		UMaterialInstanceDynamic* Material = CoolTimeImage->GetDynamicMaterial();

		if(Material)
		{
			Material->SetScalarParameterValue( "Percent" , 1.f );
			Material->SetVectorParameterValue( "Color" , ProgressBarColor[_SkillData->SkillColor] );
			Material->SetTextureParameterValue( "Mask" , _SkillData->SkillThumnail );
		}
			
		SkillThumnail->SetBrushFromTexture( _SkillData->SkillThumnail );
		
	}
}

void UPlayerSkillSlotWidget::SetCoolTimeBar(float CoolTime)
{

	UMaterialInstanceDynamic* Material = CoolTimeImage->GetDynamicMaterial();
	if (Material)
	{
		CoolTime > 0.f ? Material->SetScalarParameterValue( "Percent" , CoolTime ) : Material->SetScalarParameterValue( "Percent" , 0 );
	}
}


// <--------------------- Upgrade Skill Level --------------------->

void UPlayerSkillSlotWidget::UpgradeSkillSlotLevelUI(int32 _SkillLevel)
{
	UE_LOG(LogTemp, Log, TEXT("UpgradeSkillSlotLevelUI : %d"), _SkillLevel);
	for(int i = 0; i < _SkillLevel; i++)
		SkillLevelSlot[i]->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
}

void UPlayerSkillSlotWidget::SetSkillLockImage(bool IsSkillLock)
{
	if(IsSkillLock)
	{
		SkillLockImage->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SkillLockImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPlayerSkillSlotWidget::SetSkillComboSlotUI(bool IsCanCombo)
{
	if(IsCanCombo)
	{
		CanComboImage->SetVisibility(ESlateVisibility::Visible);
		PlayAnimation(ComboClickAnimation);
	}
	else
	{
		CanComboImage->SetVisibility(ESlateVisibility::Hidden);
	}
}
