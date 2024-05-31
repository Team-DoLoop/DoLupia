// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"

class UDataTable;
struct FDialogueData;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category="Dialog")
	void StartDialog( AActor* InCurrentNPC, const FString& NPCNmae , int32 StartubgDialogID );

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	void AdvanceDialog();

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	FString GetCurrentSpeaker() const;

	UFUNCTION( BlueprintCallable , Category = "Dialog" )
	FString GetCurrentDialogText() const;

private:
	UPROPERTY( EditAnywhere , Category = "Dialogue" )
	UDataTable* DialogueDataTable;

	UPROPERTY( EditAnywhere , Category = "Dialogue" )
	TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY()
	UUserWidget* DialogueWidget;

	FString CurrentNPCName;
	int32 CurrentDialogueID;
	FDialogueData* CurrentDialogue;

	UPROPERTY()
	AActor* CurrentNPC;

	void LoadDialogue( int32 DialogueID );
	void TriggerQuest();
	void ShowDialogWidget();
	void HideDialogWidget();

};
