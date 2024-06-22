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

	UFUNCTION()
	void MoveChapter1();

	UFUNCTION()
	void MoveChapter2();

	UFUNCTION()
	void MoveChapter3();

private:
	UPROPERTY( meta = (BindWidget) )
	UButton* Start;

	UPROPERTY( meta = (BindWidget) )
	UButton* ReStart;

	UPROPERTY( meta = (BindWidget) )
	UButton* End;

	UPROPERTY( meta = (BindWidget) )
	UButton* Chapter1;

	UPROPERTY( meta = (BindWidget) )
	UButton* Chapter2;

	UPROPERTY( meta = (BindWidget) )
	UButton* Chapter3;

};
