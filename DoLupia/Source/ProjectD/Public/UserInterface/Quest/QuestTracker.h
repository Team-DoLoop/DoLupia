// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestTracker.generated.h"

class UWidgetQuestLog_Objective;

UCLASS()
class PROJECTD_API UQuestTracker : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override; // 함수 시그니처 정리
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY( EditAnywhere )
	class AQuest_Base* QuestActor;

	UFUNCTION()
	void WidgetUpdate();

	UFUNCTION()
	void Update( AQuest_Base* UP_QuestActor );

	UFUNCTION()
	void Remove();
	
	UFUNCTION()
	void QuestCompleted( AQuest_Base* QC_QuestActor );

	UFUNCTION()
	void OnObjectiveHeard();

protected:
	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_QuestName;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_ToPotal;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UTextBlock* txt_ToRobot;

	UPROPERTY( EditAnywhere , BlueprintReadOnly , meta = (BindWidget) )
	class UVerticalBox* box_Objectives;
	
	UPROPERTY( EditAnywhere )
	TSubclassOf<UWidgetQuestLog_Objective> Objective_Widget;

	UPROPERTY()
	class UQuestLogComponent* QuestLogComp;

	template<typename T>
	bool IsObjectValid( T* Object , const FString& ObjectName );

};
template <typename T>
bool UQuestTracker::IsObjectValid( T* Object , const FString& ObjectName )
{
	if (!Object)
	{
		UE_LOG( LogTemp , Error , TEXT( "%s is invalid." ) , *ObjectName );
		return false;
	}
	return true;
}
