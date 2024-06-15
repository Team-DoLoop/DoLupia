// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

class UPlayerTutorialComp;
class UProjectDGameInstance;
class AProjectDCharacter;
class UImage;
struct FTutorialData;
/**
 * 
 */
UCLASS()
class PROJECTD_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()


	// <---------- Game ---------->
public:

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
	AProjectDCharacter* Player;

	UPROPERTY()
	UProjectDGameInstance* GI;

	UPROPERTY()
	UPlayerTutorialComp* PlayerTutorialComp;

	
	// <---------- UI ---------->
public:
	void ShowTutorialWidget(FTutorialData* _TutoData, int32 _Index );
	
	UFUNCTION()
	void NextTutorialBtn();

	void ChangeNextBtn(FString _Str);
	void SetVisibleTabImage(bool IsVisible);

private:

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TXT_Explain;

	UPROPERTY(EditDefaultsOnly, Transient, meta = (BindWidgetAnim))
	class UWidgetAnimation* TabPressAnim;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Img_Tab_Bottom;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UImage* Img_Tab;
	
	// UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	// class UButton* Btn_Next;

	//UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	//class UTextBlock* TXT_Next;

	
	// <---------- Typing ---------->
public:
	void TypeNextCharacter();
	void SkipTypingAnimation();
	bool IsTyping() const;
	
private:
	FText FullText;
	FString CurrentText;
	int32 CurrentIndex;
	FTimerHandle ToToTypingTimerHandle;
	float TypingSpeed;

	
};
