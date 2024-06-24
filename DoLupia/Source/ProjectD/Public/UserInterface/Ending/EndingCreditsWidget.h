// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingCreditsWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UEndingCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* EndingCreditsAnim;

	FWidgetAnimationDynamicEvent EndDelegate;

	UFUNCTION()
	void AnimationFinished();
};
