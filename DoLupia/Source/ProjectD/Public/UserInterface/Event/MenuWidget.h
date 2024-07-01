// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;

UCLASS()
class PROJECTD_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

private:
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UButton* Btn_Lobby;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UButton* Btn_Restart;

public:
	UFUNCTION()
	void Restart();

	UFUNCTION()
	void GotoLobby();

	UFUNCTION()
	void OpenMenu();
	
};
