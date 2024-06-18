// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Quest/QuestInteractionInterface.h"
#include "StrangeObject.generated.h"

class UNPCInteractionWidget;
class UBoxComponent;
class UMeshComponent;
class UMapIconComponent;

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
	FTimerHandle TimerHandle;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent; // BoxComponent 포인터 생성

	UPROPERTY( VisibleAnywhere )
	UMeshComponent* MeshComponent; // BoxComponent 포인터 생성

	UPROPERTY( EditAnywhere )
	FString ObjectID;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UNPCInteractionWidget> NPCInteractWidget;

	UPROPERTY()
	UNPCInteractionWidget* NPCInteractGWidget;

	virtual FString InteractWith() override;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class UMapIconComponent* MapIcon;

	void ActiveMapIcon( bool onoff );

};
