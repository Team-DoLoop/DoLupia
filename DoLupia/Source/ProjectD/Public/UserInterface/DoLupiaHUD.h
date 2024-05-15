// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DoLupiaHUD.generated.h"

struct FInteractableData;
class UMainMenu;
class UInteractionWidget;

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

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractableData) const;

	FORCEINLINE bool IsMenuVisible() const { return bISMenuVisible; }
	FORCEINLINE UMainMenu* GetMainMeun() const { return MainMenuWidget; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UMainMenu> MainMenuFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetFactory;

	bool bISMenuVisible;

	UPROPERTY()
	UMainMenu* MainMenuWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;

};
