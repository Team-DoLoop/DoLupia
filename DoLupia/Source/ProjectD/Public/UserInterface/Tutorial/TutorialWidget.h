// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	void ShowTutorialWidget();

	
private:
	float FadeOutTime = 1.0f; // 클수록 빨리 사라짐

	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TXT_Explain;

	UPROPERTY(EditDefaultsOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* FadeOutAnim;
};
