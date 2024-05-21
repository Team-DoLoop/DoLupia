// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBattleWidget.generated.h"

/**
 * 
 */
class UPlayerHPWidget;

UCLASS()
class PROJECTD_API UPlayerBattleWidget : public UUserWidget
{
	GENERATED_BODY()


	// <------------------ HP ------------------>
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UPlayerHPWidget* PlayerHPBar;

public:
	FORCEINLINE UPlayerHPWidget* GetPlayerHPBar() const {return PlayerHPBar;}


	// <------------------ MP ------------------>
private:

public:
	
};
