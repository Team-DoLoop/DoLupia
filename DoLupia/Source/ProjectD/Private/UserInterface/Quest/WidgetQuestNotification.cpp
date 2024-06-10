// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/WidgetQuestNotification.h"

#include "Components/TextBlock.h"

void UWidgetQuestNotification::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(txt_ObjectiveText)
	{
		if(!ObjectiveText.IsEmpty())
		{
			FText OT_Text = FText::FromString( ObjectiveText );
			txt_ObjectiveText->SetText( OT_Text );
		}
	}
}

void UWidgetQuestNotification::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ani_Appear) // 애니메이션이 유효한지 확인
	{
		// 애니메이션을 재생
		PlayAnimation( ani_Appear , 0.0f , 1 , EUMGSequencePlayMode::Forward , 1.0f ); // 속도, 반복 횟수 등 설정 가능
	}

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {
				// UI 작업은 게임 스레드에서 실행
				// UI 업데이트 또는 Slate 관련 작업
			RemoveFromParent();
		} ,
		1.0f , // 지연 시간(초)
		false
		);
		
}

void UWidgetQuestNotification::NativeDestruct()
{
	Super::NativeDestruct();
}
