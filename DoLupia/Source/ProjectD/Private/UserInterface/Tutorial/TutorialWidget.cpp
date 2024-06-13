// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Tutorial/TutorialWidget.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerTutorialComp.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Data/TutorialData.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"

void UTutorialWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PlayerTutorialComp = Player->GetTutorialComp();

	Btn_Next->OnClicked.AddDynamic(this, &UTutorialWidget::NextTutorialBtn);
}

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UTutorialWidget::ShowTutorialWidget(FTutorialData* _TutoData, int32 _Index)
{
	// 데이터가 없다면 끝내기
	if(!_TutoData) return;
	
	UE_LOG(LogTemp, Log, TEXT("ShowTutorialWidget TutoData Index : %d"), _Index);
	
	// 데이터로 세팅
	FText ExplainText = FText::FromString(_TutoData->TutorialWidgetData.StoryExplainText[_Index]);
	TXT_Explain->SetText(ExplainText);
}

// 버튼을 눌렀다면 다음 데이터로 세팅
void UTutorialWidget::NextTutorialBtn()
{
	PlayerTutorialComp->NextTutorial();
}

void UTutorialWidget::ChangeNextBtn(FString _Str)
{
	// TXT_Next->SetText(FText::FromString(_Str));
}

