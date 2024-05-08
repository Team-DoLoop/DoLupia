// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetQuestLog_QuestEntry.generated.h"

/**
 * 
 */

 // Delegate 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnQuestSelected , FName , QuestID );

UCLASS()
class PROJECTD_API UWidgetQuestLog_QuestEntry : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual auto NativePreConstruct() -> void override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnButtonClicked();

	// Event Dispatcher 선언
	UPROPERTY( BlueprintAssignable , Category = "Events" )
	FOnQuestSelected OnQuestSelected;

	UPROPERTY( EditAnywhere ) //expose on spawn
	FName QuestID;

protected:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadOnly, meta = (BindWidget) )
	class UCheckBox* box_ISComplete;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UButton* btn_QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FDataTableRowHandle QuestData;
};
