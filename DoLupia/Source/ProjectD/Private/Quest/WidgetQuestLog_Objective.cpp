// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/WidgetQuestLog_Objective.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Quest/Quest_Base.h"

void UWidgetQuestLog_Objective::NativePreConstruct()
{
    Super::NativePreConstruct();

    // ObjectiveData 유효성 검사
    if (ObjectiveData.ObjectiveID.IsEmpty())
    {
        UE_LOG( LogTemp , Warning , TEXT( "ObjectiveData.ObjectiveID is empty." ) );
        return; // 유효하지 않으면 조기 종료
    }

    for (const auto& KeyValue : ObjectiveData.ObjectiveID_Quantity) 
    {
        // 포맷된 텍스트 생성
        FText Template = FText::FromString( "{desc} {current} / {quantity}" );

        FFormatNamedArguments Args;
        Args.Add( "desc" , FText::FromString( ObjectiveData.Description ) );

        if (QuestActor)
        {
            int32* currentValue = QuestActor->CurrentObjectiveProgress.Find( KeyValue.Key );
            Args.Add( "current" , FText::AsNumber( *currentValue ) ); // 초기값을 0으로 설정
            UE_LOG( LogTemp , Warning , TEXT( "QuestActor _ currnetValue" ) );

            // check_IsCompleted 유효성 검사 및 초기화
            if (check_IsCompleted)
            {
                auto checkbox = (KeyValue.Value <= *currentValue) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;

                check_IsCompleted->SetCheckedState( checkbox ); // 체크박스 초기화
            }
            else
            {
                UE_LOG( LogTemp , Warning , TEXT( "check_IsCompleted is not bound." ) );
            }
        }
		else
	    {
	        Args.Add( "current" , FText::AsNumber( 0 ) ); // 초기값을 0으로 설정
	        UE_LOG( LogTemp , Warning , TEXT( "QuestActor invalid UWidgetQuestLog_Objective" ) );
	    }

	    Args.Add( "quantity" , FText::AsNumber( KeyValue.Value ) );
		
	    FText FormattedText = FText::Format( Template , Args );

	    // txt_Description 유효성 검사
	    if (txt_Description)
	    {
	        txt_Description->SetText( FormattedText ); // 포맷된 텍스트 설정
	    }
	    else
	    {
	        UE_LOG( LogTemp , Warning , TEXT( "txt_Description is not bound." ) );
	    }
    }
}

void UWidgetQuestLog_Objective::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetQuestLog_Objective::NativeDestruct()
{
	Super::NativeDestruct();
}
