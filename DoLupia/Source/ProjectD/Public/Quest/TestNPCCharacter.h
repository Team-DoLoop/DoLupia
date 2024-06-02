// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Quest/QuestInteractionInterface.h"
#include "TestNPCCharacter.generated.h"

class UNPCInteractionWidget;
class UQuestGiver;
class UBoxComponent;
class UDialogComponent;

UCLASS()
class PROJECTD_API ATestNPCCharacter : public ACharacter, public IQuestInteractionInterface
{
	GENERATED_BODY()

public:
	ATestNPCCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY( EditAnywhere )
	TSubclassOf<UNPCInteractionWidget> NPCInteractWidget;

	UPROPERTY()
	UNPCInteractionWidget* NPCInteractGWidget;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UQuestGiver* GetQuestGiver() const { return QuestGiverComp; };

	virtual FString InteractWith() override;

	virtual void LookAt() override;
	void DialogWith();

	UPROPERTY( VisibleAnywhere )
	UBoxComponent* BoxComponent; // BoxComponent 포인터 생성

private:
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	UQuestGiver* QuestGiverComp;

	UPROPERTY( VisibleAnywhere , Category = "Dialog" )
	UDialogComponent* DialogComp;
};
