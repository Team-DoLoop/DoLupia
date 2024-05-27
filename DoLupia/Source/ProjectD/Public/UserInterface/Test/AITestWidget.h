﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "AITestWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UAITestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SendChatbotSV();

	UFUNCTION()
	void SendImgaiSV();

	UFUNCTION()
	void ChangeMaterial();


private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_chatbot;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_imgAI;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_MLoad;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UEditableText* edit_sendText;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_chatbot;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UImage* img_aitexture;

	UPROPERTY( EditDefaultsOnly )
	class UAIConnectionLibrary* connectionLibrary;

	UPROPERTY()
	class APlayerGameMode* gm;

};
