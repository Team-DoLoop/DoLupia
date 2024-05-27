// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized ( ) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UHorizontalBox* SkillBox;

	UPROPERTY ( EditDefaultsOnly )
	TSubclassOf<class UPlayerSkillSlotWidget> PlayerSkillSlotFactory;

	UPROPERTY ( VisibleDefaultsOnly )
	TArray<class UPlayerSkillSlotWidget*> PlayerSkillSlotArray;
	
public:
	void InitSkillSlot();
	
};
