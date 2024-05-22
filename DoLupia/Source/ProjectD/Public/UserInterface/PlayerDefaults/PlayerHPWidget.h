// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UPlayerHPWidget : public UUserWidget
{
	GENERATED_BODY()


private :
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* HPBar;

protected:

public:
	void SetHPBar(int32 _HP, int32 _MaxHP);
};
