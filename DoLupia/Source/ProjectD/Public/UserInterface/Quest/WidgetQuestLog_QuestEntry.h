// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestLog_QuestEntry.generated.h"

/**
 * 
 */

 // Delegate 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnQuestSelected , FName , QuestID , AQuest_Base*, QuestActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnTracked , AQuest_Base* , QuestActor );

UCLASS()
class PROJECTD_API UWidgetQuestLog_QuestEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnTrackButtonClicked();

	// Event Dispatcher 선언
	UPROPERTY( BlueprintAssignable , Category = "Events" )
	FOnQuestSelected OnQuestSelected;

	UPROPERTY( BlueprintAssignable , Category = "Events" )
	FOnTracked OnTracked;

	UPROPERTY( EditAnywhere ) //expose on spawn
	FName QuestID;

	UPROPERTY(EditAnywhere)
	class AQuest_Base* QuestActor;

protected:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadOnly, meta = (BindWidget) )
	class UCheckBox* box_ISComplete;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FDataTableRowHandle QuestData;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_Track;
};
