// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCConvWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UNPCConvWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void SetupNPCConv(FString conv);

private:
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* txt_NPCConv;

	
};
