// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerEvasionSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerEvasionSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateEvasionCoolTimeUI(float CoolTime);

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* CoolTimeImage;
};
