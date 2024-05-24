// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APlayerGameMode();

	virtual void StartPlay() override;

	UAIConnectionLibrary* GetAIConnectionLibrary() const;

	void InitializeNPCConvWidget();
	void ReceiveNPCMsg(FString msg);

	UPROPERTY( BlueprintReadOnly )
	class UNPCConvWidget* NPCConvUI;

private:

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;

};
