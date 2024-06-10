// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LocationTitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API ULocationTitleWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_LocationName;

	UPROPERTY( Transient , BlueprintReadOnly , meta = (BindWidgetAnim) )
	class UWidgetAnimation* ani_Title;

	UPROPERTY( EditAnywhere )
	FString LocationTitleText;

};
