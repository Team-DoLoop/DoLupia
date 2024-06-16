// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Skill/PlayerEvasionSlotWidget.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UPlayerEvasionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UMaterialInstanceDynamic* Material = CoolTimeImage->GetDynamicMaterial();

	if(Material)
	{
		Material->SetScalarParameterValue( "Percent" , 1.f );
		Material->SetVectorParameterValue( "Color" , FLinearColor( 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.5f));
	}
}

void UPlayerEvasionSlotWidget::UpdateEvasionCoolTimeUI(float CoolTime)
{
	UMaterialInstanceDynamic* Material = CoolTimeImage->GetDynamicMaterial();
	if (Material)
	{
		CoolTime > 0.f ? Material->SetScalarParameterValue( "Percent" , CoolTime ) : Material->SetScalarParameterValue( "Percent" , 0 );
	}
}
