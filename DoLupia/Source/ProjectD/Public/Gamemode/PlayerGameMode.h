// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameMode.generated.h"


class UAIConnectionLibrary;
class UNPCConvWidget; 
class UAITestWidget; 

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

	class UAIConnectionLibrary* GetAIConnectionLibrary() const;

	void InitializeNPCConvWidget();
	void ReceiveNPCMsg(FString msg);

	// 2024.05.26 Player / Boss 텍스처 변경 분기처리
	void ApplyAITxtP();
	void ApplyAITxtB();

	UPROPERTY( BlueprintReadOnly )
	class UNPCConvWidget* NPCConvUI;

	UPROPERTY( BlueprintReadOnly )
	class UAITestWidget* AITestUI;


private:

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> AITestUIFactory;


};
