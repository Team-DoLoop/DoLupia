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
	virtual void BeginPlay() override;

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
	UPROPERTY()
	TArray<FName> LevelNames;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* AIlib;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UUserWidget> NPCUIFactory;


	/*---------- Level 별 bgm ----------*/
public:
	// 레벨에 대한 BGM을 재생하는 함수
	void PlayBGMForLevel( int32 LevelIndex );

protected:
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "BGM" )
	TMap<int32 , USoundWave*> LvBGMs;

	UPROPERTY( Transient )
	USoundBase* CurrentBGM;

private:
	int32 LevelIdx;
};
