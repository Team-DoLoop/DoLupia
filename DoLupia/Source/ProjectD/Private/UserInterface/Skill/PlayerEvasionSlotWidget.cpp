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
	}
}

void UPlayerEvasionSlotWidget::UpdateEvasionCoolTimeUI(float CoolTime)
{
	UMaterialInstanceDynamic* Material = CoolTimeImage->GetDynamicMaterial();
	if (Material)
	{

		if(CoolTime > 0.f)
		{
			Material->SetScalarParameterValue( "Percent" , CoolTime );
			Material->SetScalarParameterValue( "Opacity" , 1.f );
		}
		else
			Material->SetScalarParameterValue( "Percent" , 0 );

	}
}
