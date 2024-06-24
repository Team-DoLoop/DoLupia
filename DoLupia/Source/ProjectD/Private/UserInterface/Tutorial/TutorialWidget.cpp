// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Tutorial/TutorialWidget.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerTutorialComp.h"
#include "Components/Image.h"
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

	// Btn_Next->OnClicked.AddDynamic(this, &UTutorialWidget::NextTutorialBtn);
}

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibleTabImage(false);
	TypingSpeed = 0.1f; 
	CurrentIndex = 0;
}

	
// <-------------------- UI -------------------->

void UTutorialWidget::ShowTutorialWidget(FTutorialData* _TutoData, int32 _Index)
{
	// 데이터가 없다면 끝내기
	if(!_TutoData) return;
	
	UE_LOG(LogTemp, Log, TEXT("ShowTutorialWidget TutoData Index : %d"), _Index);
	
	if(TXT_Explain)
	{
		// 데이터로 세팅
		FText ExplainText = FText::FromString(_TutoData->TutorialWidgetData.StoryExplainText[_Index]);
		
		FullText = ExplainText;
		CurrentText = "";
		CurrentIndex = 0;

		TXT_Explain->SetText( FText::FromString( CurrentText ) );
		
		// 타이핑 시작
		GetWorld()->GetTimerManager().SetTimer( ToToTypingTimerHandle , this , &UTutorialWidget::TypeNextCharacter , TypingSpeed , true );
	}
}

// 버튼을 눌렀다면 타이핑인지 확인하고 아니라면 넘어가기
void UTutorialWidget::NextTutorialBtn()
{
	if (IsTyping())
	{
		UE_LOG(LogTemp, Log, TEXT("IsTyping : false"));
		SkipTypingAnimation();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("IsTyping : true"));
		SetVisibleTabImage(false);
		PlayerTutorialComp->NextTutorial();
	}
}

void UTutorialWidget::ChangeNextBtn(FString _Str)
{
	// TXT_Next->SetText(FText::FromString(_Str));
}

void UTutorialWidget::SetVisibleTabImage(bool IsVisible)
{
	if(IsVisible)
	{
		Img_Tab_Bottom->SetVisibility(ESlateVisibility::Visible);
		Img_Tab->SetVisibility(ESlateVisibility::Visible);

		// WidgetAnimation, StartAtTime, NumLoopsToPlay(0 = Loop), EUMGSequencePlayMode, PlaybackSpeed, bRestoreState
		PlayAnimation(TabPressAnim, 0, 0, EUMGSequencePlayMode::Forward, 2, true);
	}
	else
	{
		Img_Tab_Bottom->SetVisibility(ESlateVisibility::Hidden);
		Img_Tab->SetVisibility(ESlateVisibility::Hidden);
	}
}


// <-------------------- Typing -------------------->

void UTutorialWidget::TypeNextCharacter()
{
	if (CurrentIndex < FullText.ToString().Len())
	{
		CurrentText += FullText.ToString()[CurrentIndex];
		TXT_Explain->SetText(FText::FromString(CurrentText));
		CurrentIndex++;
	}
	else
	{
		SetVisibleTabImage(true);
		GetWorld()->GetTimerManager().ClearTimer( ToToTypingTimerHandle );
	}
}

void UTutorialWidget::SkipTypingAnimation()
{
	// Stop the typing timer to display full text immediately
	GetWorld()->GetTimerManager().ClearTimer( ToToTypingTimerHandle );

	// Show full text
	TXT_Explain->SetText( FullText );
	
	SetVisibleTabImage(true);
}

bool UTutorialWidget::IsTyping() const
{
	return ToToTypingTimerHandle.IsValid();
}
