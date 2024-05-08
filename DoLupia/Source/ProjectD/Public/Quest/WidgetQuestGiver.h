﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Struct_QuestSystem.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestGiver.generated.h"

class UWidgetQuestLog_Objective;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class PROJECTD_API UWidgetQuestGiver : public UUserWidget
{
	GENERATED_BODY()

public:

    virtual auto NativePreConstruct() -> void override;

    virtual void NativeConstruct() override;

    virtual void NativeDestruct() override;

    UFUNCTION()
    void OnAcceptClicked();

    UFUNCTION()
    void OnDeclineClicked();

    UPROPERTY( EditAnywhere ) //expose on spawn
	FQuestDetails QuestDetails;

    UPROPERTY( EditAnywhere ) //expose on spawn
	FName QuestID;

    UPROPERTY( meta = (BindWidget) )
    UVerticalBox* box_Objectives;
	
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

    UPROPERTY( EditAnywhere )
    TSubclassOf<UWidgetQuestLog_Objective> Objective_Widget;

};
