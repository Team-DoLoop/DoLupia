// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ProjectDCharacter.h"
#include "GameFramework/Actor.h"
#include "Quest/Struct_QuestSystem.h"
#include "Quest_Base.generated.h"

class AQuestLogComponent;
class UWidgetQuestNotification;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnObjectiveHeard );
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

	//UPROPERTY()
	FOnObjectiveHeard OnObjectiveHeard;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnObjectiveIDHeard( FString ObjectiveID , int32 Value = 1 );

	UFUNCTION()
	void GetQuestDetails();

	UFUNCTION()
	void CheckItem();

	UFUNCTION()
	void OnQuestDataLoadedHandler( FName QuestID );

	UFUNCTION()
	void IsObjectiveComplete( FString ObjectiveID );

	UFUNCTION()
	bool AreObjectivesComplete();

	UFUNCTION()
	FObjectiveDetails GetObjectiveDataByID( FString ObjectiveID );

	UPROPERTY(EditAnywhere) //expose on spawn 안됨
	FName QuestID;

	UPROPERTY()
	FQuestDetails QuestDetails;

	UPROPERTY( EditAnywhere )
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

	UPROPERTY(EditAnywhere)
	bool IsTurnedIn;

protected:
	bool Local_AllComplete;

};
