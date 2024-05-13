// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Quest/QuestInteractionInterface.h"
#include "QuestGiver.generated.h"


class UWidgetQuestGiver;
class UWidgetQuestRewards;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UQuestGiver : public UActorComponent, public IQuestInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestGiver();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle QuestData;

	UFUNCTION()
	void DisplayQuest();

	UFUNCTION()
	void DisplayRewards();

	UPROPERTY()
	class AProjectDCharacter* MyPlayerCharacter;
	UPROPERTY()
	class AProjectDGameMode* MyGameMode;

	UFUNCTION(BlueprintCallable)
	virtual FString InteractWith() override;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UWidgetQuestGiver> QuestGiverWidget;

	UPROPERTY()
	UWidgetQuestGiver* QuestWidget;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UWidgetQuestRewards> QuestRewardsWidget;

	UPROPERTY()
	UWidgetQuestRewards* RewardsWidget;
};
