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

	void InitializeNPCConvWidget();

	void ReceiveNPCConv( const FString& conv );

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;

	UPROPERTY( BlueprintReadOnly )
	class UNPCConvWidget* NPCConvUI;

	FString test;

//private:
	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;
	
};
