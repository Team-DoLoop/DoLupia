// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class PROJECTD_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	void UpdateDialogText( FText NewText );

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	void UpdateSpeakerText( FText NewSpeaker );

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	void SetCurrentNPC(AActor* InCurrentNPC);

private:
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UTextBlock* txt_speaker;


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* txt_dialog;
	
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UButton* btn_nxt;

	UFUNCTION()
	void OnNxtBtnClicked();

	AActor* CurrentNPC;

	
};
