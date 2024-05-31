// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Quest/QuestInteractionInterface.h"
#include "StrangeObject.generated.h"

class UNPCInteractionWidget;
class UBoxComponent;

UCLASS()
class PROJECTD_API AStrangeObject : public AActor, public IQuestInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrangeObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UNPCInteractionWidget> NPCInteractWidget;

	UPROPERTY()
	UNPCInteractionWidget* NPCInteractGWidget;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "UI" )
	UWidgetComponent* WidgetComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent; // BoxComponent 포인터 생성

	UPROPERTY( EditAnywhere )
	FString ObjectID;

	virtual FString InteractWith() override;

};
