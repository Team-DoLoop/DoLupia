#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" // UUserWidget 정의
#include "Struct_QuestSystem.h" // FDataTableRowHandle 포함
#include "Components/VerticalBox.h"
#include "WidgetQuestLog.generated.h"

class UWidgetQuestLog_Objective;
class UTextBlock; 
class UScrollBox;
class UWidgetSwitcher;
class UButton;
class UWidgetQuestLog_QuestEntry;

// Event Delegate 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FQuestSelected , FName , QuestID );

UCLASS()
class PROJECTD_API UWidgetQuestLog : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativePreConstruct() override; // 함수 시그니처 정리
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    // Event Dispatcher
    UPROPERTY( BlueprintAssignable , Category = "Events" )
    FQuestSelected QuestSelected;

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

    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FDataTableRowHandle QuestData;

    // 함수 정의
    UFUNCTION()
    void OnButtonClicked();

    UFUNCTION()
    void OnQuestSelected( FName QuestID );

    UFUNCTION()
    void DisplayQuest( FName QuestID );

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
