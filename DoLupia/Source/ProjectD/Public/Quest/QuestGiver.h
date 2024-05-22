// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Quest/QuestInteractionInterface.h"
#include "QuestGiver.generated.h"


class UItemBase;
class UWidgetQuestGiver;
class UWidgetQuestRewards;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UQuestGiver : public UActorComponent, public IQuestInteractionInterface
{
	GENERATED_BODY()

public:	
	UQuestGiver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE UWidgetQuestGiver*		GetWidgetQuestGiver() const { return QuestWidget; }
	FORCEINLINE UWidgetQuestRewards*	GetRewardQuestGiver() const { return RewardsWidget; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle QuestData;

	UFUNCTION()
	void DisplayQuest();

	UFUNCTION()
	void DisplayRewards();

	UFUNCTION()
	UItemBase* CreateItem( const TSubclassOf<UItemBase> BaseClass , const int32 InQuantity );

	UPROPERTY( EditInstanceOnly)
	UDataTable* ItemDataTable;

	UPROPERTY( EditInstanceOnly )
	FName DesiredItemID;

	UPROPERTY( VisibleAnywhere )
	UItemBase* ItemReference;

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
