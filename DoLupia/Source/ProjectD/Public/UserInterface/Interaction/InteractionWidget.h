// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

struct FInteractableData;
class AProjectDCharacter;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class PROJECTD_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget(const FInteractableData* InteractableData) const;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(Category = "Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
	AProjectDCharacter* PlayerReference;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UProgressBar* InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	float CurrentInteractionDuration;

	

};
