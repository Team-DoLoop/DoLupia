// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Ending/EndingCreditsWidget.h"

#include "Kismet/GameplayStatics.h"

void UEndingCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UEndingCreditsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	EndDelegate.BindDynamic(this, &UEndingCreditsWidget::AnimationFinished);
	BindToAnimationFinished(EndingCreditsAnim, EndDelegate);
	
	PlayAnimation(EndingCreditsAnim);
}

void UEndingCreditsWidget::AnimationFinished()
{
	UE_LOG(LogTemp, Log, TEXT("Ending Credits End"));

	UGameplayStatics::OpenLevel( this , TEXT("Opening") );
}
