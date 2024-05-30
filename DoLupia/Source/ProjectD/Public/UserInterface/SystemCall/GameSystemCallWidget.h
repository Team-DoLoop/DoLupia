// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSystemCallWidget.generated.h"

class USoundCue;
class USoundWave;
class UTextBlock;
class UWidgetAnimation;

DECLARE_MULTICAST_DELEGATE_OneParam( FOnSystemCallDelegate , const FText&);
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSystemCallDelegateSoundCue , const FText& , USoundCue* );
DECLARE_MULTICAST_DELEGATE_TwoParams( FOnSystemCallDelegateSoundWave , const FText& , USoundWave*);



UCLASS()
class PROJECTD_API UGameSystemCallWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FOnSystemCallDelegate OnSystemCall;
	FOnSystemCallDelegateSoundCue OnSystemCallSoundCue;
	FOnSystemCallDelegateSoundWave OnSystemCallSoundWave;

	void DisplayMessage( const FText& Message );
	void DisplayMessage( const FText& Message , USoundCue* SoundCue );
	void DisplayMessage( const FText& Message , USoundWave* SoundWave );

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY( meta = (BindWidget) )
	UTextBlock* SystemText;

	UPROPERTY( BlueprintReadOnly , Category = "BindAnimation" , meta = (BindWidgetAnim) , Transient )
	UWidgetAnimation* FadeAnimation; // 애니메이션 변수 선언
};
