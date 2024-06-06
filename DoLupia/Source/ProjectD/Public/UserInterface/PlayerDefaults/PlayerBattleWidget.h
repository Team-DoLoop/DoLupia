// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBattleWidget.generated.h"

class UPlayerEvasionSlotWidget;
/**
 * 
 */
enum class EUseColor : uint8;
class UPlayerHPWidget;
class UPlayerMPWidget;
class UPlayerSkillWidget;
class UProjectDGameInstance;

UCLASS()
class PROJECTD_API UPlayerBattleWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized ( ) override;
	
	// <------------------ HP ------------------>
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UPlayerHPWidget* PlayerHPBar;

public:
	FORCEINLINE UPlayerHPWidget* GetPlayerHPBar() const {return PlayerHPBar;}


	// <------------------ MP ------------------>
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UPlayerMPWidget* PlayerMPBar;
	
public:
	FORCEINLINE UPlayerMPWidget* GetPlayerMPBar() const {return PlayerMPBar;}


	// <------------------ Skill ------------------>
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UPlayerSkillWidget* PlayerSkillUI;
	
public:
	FORCEINLINE UPlayerSkillWidget* GetPlayerSkillUI() const {return PlayerSkillUI;}

	
	// <------------------ Evasion ------------------>
private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UPlayerEvasionSlotWidget* PlayerEvasionSlotUI;

public:
	FORCEINLINE UPlayerEvasionSlotWidget* GetPlayerEvasionSlotUI() const {return PlayerEvasionSlotUI;}

	
};
