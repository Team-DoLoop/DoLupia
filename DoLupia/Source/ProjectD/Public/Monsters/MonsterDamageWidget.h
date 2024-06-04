// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UMonsterDamageWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* DamageText;

	void SetDamage( int32 damage );

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetAnimation* anim;
};
