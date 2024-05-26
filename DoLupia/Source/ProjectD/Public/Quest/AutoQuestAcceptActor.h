// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "AutoQuestAcceptActor.generated.h"

UCLASS()
class PROJECTD_API AAutoQuestAcceptActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutoQuestAcceptActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditAnywhere , BlueprintReadWrite )
	FDataTableRowHandle QuestData;
	
	UFUNCTION(BlueprintCallable)
	void GiveQuest();

	UPROPERTY()
	class AProjectDCharacter* MyPlayerCharacter;

};
