// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

class UPlayerTutorialComp;
class UProjectDGameInstance;
class AProjectDCharacter;
struct FTutorialData;
/**
 * 
 */
UCLASS()
class PROJECTD_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void ShowTutorialWidget(FTutorialData* _TutoData);

	UFUNCTION()
	void NextTutorialBtn();

	void ChangeNextBtn(FString _Str);
	
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

	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* TXT_Explain;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* Btn_Next;

	//UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	//class UTextBlock* TXT_Next;
	
};
