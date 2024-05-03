// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UMonsterHPWidget : public UUserWidget
{
	GENERATED_BODY()
public: 
	virtual void NativeConstruct() override;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UProgressBar* MonsterHPBar;

	void SetHP( int32 hp , int32 maxHP );

	UPROPERTY()
	class AMonster* me;
};
