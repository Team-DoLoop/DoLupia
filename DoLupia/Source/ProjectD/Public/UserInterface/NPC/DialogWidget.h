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

	void UpdateDialogText( FText NewText );
	void UpdateSpeakerText( FText NewSpeaker );

private:
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UTextBlock* txt_speaker;


	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UTextBlock* txt_dialog;
	
	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	UButton* btn_nxt;

	
};
