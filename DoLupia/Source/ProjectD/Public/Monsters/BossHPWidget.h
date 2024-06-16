// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UBossHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetHP( int32 hp , int32 maxHP );

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* BossHPBar;

	UPROPERTY()
	class ABossMonster* Boss;


};
