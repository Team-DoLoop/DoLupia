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

	void InitializeNPCConvWidget();

	void ReceiveNPCConv( FString Response );

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;

	UPROPERTY( BlueprintReadOnly )
	class UNPCConvWidget* NPCConvUI;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	FString NPCConversation;
	
};
