// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestNotification.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UWidgetQuestNotification : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;


	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_ObjectiveText;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UImage* img_Check_Empty;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UImage* img_CheckComplete;

	UPROPERTY( Transient , BlueprintReadOnly, meta = (BindWidgetAnim) )
	class UWidgetAnimation* ani_Appear;

	UPROPERTY(EditAnywhere)
	FString ObjectiveText;

	UPROPERTY( EditAnywhere )
	USoundWave* SuccessSoundWave;
	
};
