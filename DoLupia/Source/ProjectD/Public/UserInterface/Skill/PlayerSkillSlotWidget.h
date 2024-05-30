// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillSlotWidget.generated.h"

/**
 * 
 */
struct FPlayerSkillData;
UCLASS()
class PROJECTD_API UPlayerSkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized ( ) override;
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* SkillThumnail;
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* CoolTimeBar;
	
public:
	void InitUI();
	void SetUI(FPlayerSkillData* PlayerSkillData);
	void SetCoolTimeBar(float CoolTime);
	
};
