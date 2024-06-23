// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMPWidget.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class PROJECTD_API UPlayerMPWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UProgressBar* MPBar;

public:
	void SetMPBar(int32 _MP, int32 _MaxMP);
	virtual void NativeConstruct() override;

private:
	float CurrentPercent;
	float TargetPercent;
	float LerpSpeed;
	FTimerHandle UpdateTimerHandle;

	void UpdateMPBar();
	void StartUpdateTimer();
	void StopUpdateTimer();
};
