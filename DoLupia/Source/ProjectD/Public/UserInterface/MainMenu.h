// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AProjectDCharacter;
class UInventoryPannel;
/**
 * 
 */
UCLASS()
class PROJECTD_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()


public:
	FORCEINLINE UInventoryPannel* GetInventoryPanel() const { return InventoryPanel; };

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:
	UPROPERTY(meta=(BindWidget))
	UInventoryPannel* InventoryPanel;

	UPROPERTY()
	AProjectDCharacter* PlayerCharacter;

	
};
