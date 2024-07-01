// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Ending/EndingCreditsWidget.h"

#include "ProjectDGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UEndingCreditsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
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
	
	GI->ExecuteTutorial(EExplainType::MAIN_STORY, -1, 9900);
	
	// UGameplayStatics::OpenLevel( this , TEXT("Opening") );
}
