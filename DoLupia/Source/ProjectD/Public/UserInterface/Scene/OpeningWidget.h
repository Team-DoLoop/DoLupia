// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OpeningWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PROJECTD_API UOpeningWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void MoveTutorialMap();

	UFUNCTION()
	void GameEnd();

	UFUNCTION()
	void MoveSaveMap();

private:
	UPROPERTY( meta = (BindWidget) )
	UButton* Start;

	UPROPERTY( meta = (BindWidget) )
	UButton* ReStart;

	UPROPERTY( meta = (BindWidget) )
	UButton* End;

};
