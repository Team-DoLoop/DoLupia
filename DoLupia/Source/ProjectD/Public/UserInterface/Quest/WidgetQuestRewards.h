// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Quest/Struct_QuestSystem.h>

#include "WidgetQuestRewards.generated.h"

class UWidgetQuestLog_Objective;
class UItemBase;

UCLASS()
class PROJECTD_API UWidgetQuestRewards : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override; // 함수 시그니처 정리
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

    UFUNCTION()
    void OnAcceptClicked();

    //UFUNCTION()
    //void OnDeclineClicked();

    UPROPERTY( EditAnywhere ) //expose on spawn
    FQuestDetails QuestDetails;

    UPROPERTY( EditAnywhere ) //expose on spawn
    FName QuestID;

    UPROPERTY( EditAnywhere )
    TArray<UItemBase*> ItemRewards;

protected:
    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_QuestName;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_QuestDesc;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UTextBlock* txt_StageDesc;

    //UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    //class UButton* btn_Decline;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UButton* btn_Accept;

    UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
    class UHorizontalBox* box_RewardsItem;

    UPROPERTY( EditAnywhere )
    TSubclassOf<UWidgetQuestLog_Objective> Objective_Widget;

private:
    void ChangePlayerStateIdle();

};
