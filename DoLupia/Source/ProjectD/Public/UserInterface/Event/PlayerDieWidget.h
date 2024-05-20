// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerDieWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class PROJECTD_API UPlayerDieWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_ReStart;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UButton* Btn_Quit;

public:
	UFUNCTION()
	void ReStart();
	
	UFUNCTION()
	void Quit();
};
