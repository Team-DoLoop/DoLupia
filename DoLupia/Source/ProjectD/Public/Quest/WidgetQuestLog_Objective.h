// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct_QuestSystem.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestLog_Objective.generated.h"


struct FObjectiveDetails;
class UTextBlock;
class UCheckBox;
/**
 * 
 */
UCLASS()
class PROJECTD_API UWidgetQuestLog_Objective : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativePreConstruct() override; // 함수 시그니처 정리
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;


    UPROPERTY( EditAnywhere , BlueprintReadWrite )
    FObjectiveDetails ObjectiveData;

protected:
    // 위젯에 바인드할 컴포넌트 선언
    UPROPERTY( meta = (BindWidget) )
    UTextBlock* txt_Description;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    UCheckBox* check_IsCompleted;

};
