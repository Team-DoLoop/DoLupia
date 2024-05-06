// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestGiver.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API UWidgetQuestGiver : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnAcceptClicked();

    UFUNCTION()
    void OnDeclineClicked();

    UFUNCTION()
    void OnMouseChange();
	
protected:
    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_QuestName;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_QuestDesc;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_StageDesc;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UButton* btn_Decline;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UButton* btn_Accept;

};
