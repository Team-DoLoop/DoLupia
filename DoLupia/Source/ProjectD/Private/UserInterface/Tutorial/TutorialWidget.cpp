// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Tutorial/TutorialWidget.h"

void UTutorialWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTutorialWidget::ShowTutorialWidget()
{
	// 사라지는 애니메이션 실행
	// Animation, Start Time, NumberOfLoops, PlayMode, PlaybackSpeed, bRestoreState
	PlayAnimation(FadeOutAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, FadeOutTime, false);
}