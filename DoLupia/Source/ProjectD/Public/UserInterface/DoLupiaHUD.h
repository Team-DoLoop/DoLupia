// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DoLupiaHUD.generated.h"

struct FInteractableData;
class UMainMenu;
class UGameSystemCallWidget;
class UInteractionWidget;
class UItemBase;

/**
 * 
 */
UCLASS()
class PROJECTD_API ADoLupiaHUD : public AHUD
{
	GENERATED_BODY()


public:
	ADoLupiaHUD();

	void DisPlayMenu();
	void HideMenu();
	bool ToggleMenu();

	void UpdateEquipmentWidget(UItemBase* ItemBase ) const;

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	FORCEINLINE bool IsMenuVisible() const { return bISMenuVisible; }
	FORCEINLINE UMainMenu* GetMainMeun() const { return MainMenuWidget; }

	void OnSystemCall( const FText& Message ) const;
	void OnSystemCallSoundCue( const FText& Message , class USoundCue* SoundCue ) const;
	void OnSystemCallSoundWave( const FText& Message , class USoundWave* SoundWave ) const;

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetFactory;

	UPROPERTY( EditDefaultsOnly , Category = "Widgets" )
	TSubclassOf<UGameSystemCallWidget> GameSystemCallFactory;

	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

	UPROPERTY()
	UGameSystemCallWidget* GameSystemCall;

	bool bISMenuVisible;
};
