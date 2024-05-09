// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestLogComponent.h"
#include "GameFramework/Actor.h"
#include "Quest/Struct_QuestSystem.h"
#include "Quest_Base.generated.h"

class UWidgetQuestNotification;

UCLASS()
class AQuest_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	class AProjectDCharacter* ProjectDCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnObjectiveIDHeard( FString ObjectiveID );

	UFUNCTION()
	void GetQuestDetails();

	UFUNCTION()
	void OnQuestDataLoadedHandler( FName QuestID );

	UFUNCTION()
	void IsObjectiveComplete( FString ObjectiveID );

	UFUNCTION()
	FORCEINLINE FObjectiveDetails GetObjectiveDataByID( FString ObjectiveID )
	{
		for (const auto& Objective : CurrentStageDetails.Objectives)
		{
			if (Objective.ObjectiveID == ObjectiveID) {
				return Objective;
			}
		}
		// 목표 ID와 일치하는 항목을 찾지 못한 경우 기본값을 반환하거나 오류 처리를 수행할 수 있습니다.
		return FObjectiveDetails();
	}

	UPROPERTY(EditAnywhere) //expose on spawn 안됨
	FName QuestID;

	UPROPERTY()
	FQuestDetails QuestDetails;

	UPROPERTY()
	int32 CurrentStage;

	UPROPERTY()
	FStageDetails CurrentStageDetails;

	UPROPERTY()
	TMap<FString, int32> CurrentObjectiveProgress;

	UPROPERTY()
	bool IsCompleted;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FDataTableRowHandle QuestData;

	//블루프린트에서 넣어줘야해!!!!!
	UPROPERTY( EditAnywhere )
	TSubclassOf<UWidgetQuestNotification> Notification_Widget;
};
