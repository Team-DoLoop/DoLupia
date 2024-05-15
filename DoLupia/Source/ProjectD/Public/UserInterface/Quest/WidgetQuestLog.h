﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" // UUserWidget 정의
#include "Components/VerticalBox.h"
#include <Quest/Struct_QuestSystem.h>
#include "WidgetQuestLog.generated.h"

class AQuest_Base;
class UWidgetQuestLog_Objective;
class UTextBlock; 
class UScrollBox;
class UWidgetSwitcher;
class UButton;
class UWidgetQuestLog_QuestEntry;
class UQuestTracker;

UCLASS()
class PROJECTD_API UWidgetQuestLog : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativePreConstruct() override; // 함수 시그니처 정리
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;


protected:
    // 위젯에 바인드할 컴포넌트 선언
    UPROPERTY( meta = (BindWidget) )
    UTextBlock* txt_QuestName;

    UPROPERTY( meta = (BindWidget) )
    UTextBlock* txt_QuestDesc;

    UPROPERTY( meta = (BindWidget) )
    UTextBlock* txt_StageDesc;

    UPROPERTY( meta = (BindWidget) )
    UVerticalBox* box_Objectives;

    UPROPERTY( meta = (BindWidget) )
    UScrollBox* scroll_MainQuests;

    UPROPERTY( meta = (BindWidget) )
    UScrollBox* scroll_SideQuests;

    UPROPERTY( meta = (BindWidget) )
    UWidgetSwitcher* WidgetSwitcher;

    UPROPERTY( meta = (BindWidget) )
    UButton* btn_Close;

    // 클래스 멤버 변수
    UPROPERTY( EditAnywhere )
    TSubclassOf<UWidgetQuestLog_QuestEntry> QuestLog_Widget;

    UPROPERTY( EditAnywhere )
    TSubclassOf<UWidgetQuestLog_Objective> Objective_Widget;

    UPROPERTY( EditAnywhere )
    TSubclassOf<UQuestTracker> QuestTracker_Widget;

    UPROPERTY()
    class UQuestTracker* Tracker;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FDataTableRowHandle QuestData;

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    class AQuest_Base* CurrentQuestActor;

    // 함수 정의
    UFUNCTION()
    void OnButtonClicked();

    UFUNCTION()
    void OnQuestSelected( FName QuestID , AQuest_Base* QuestActor );

    UFUNCTION()
    void DisplayQuest( FName QuestID, AQuest_Base* QuestActor );

    UFUNCTION()
    void OnTracked(AQuest_Base* QuestActor);

    void AddQuestToScrollBox( UWidgetQuestLog_QuestEntry* QuestWidget , FQuestDetails* QuestDetailsRow , FName QuestID );

    void SetupPlayerController();

    template <typename T>
    bool IsObjectValid( T* Object , const FString& ObjectName ); // 유효성 검사 함수
};

// 템플릿 함수 구현
template <typename T>
bool UWidgetQuestLog::IsObjectValid( T* Object , const FString& ObjectName )
{
    if (!Object)
    {
        UE_LOG( LogTemp , Error , TEXT( "%s is invalid." ) , *ObjectName );
        return false;
    }
    return true;
}
