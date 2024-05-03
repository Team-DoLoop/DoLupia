// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Quest/QuestInteractionInterface.h"
#include "TestNPCCharacter.generated.h"

class UQuestGiver;

UCLASS()
class PROJECTD_API ATestNPCCharacter : public ACharacter, public IQuestInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestNPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UQuestGiver* GetQuestGiver() const { return QuestGiverComp; };

	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	UQuestGiver* QuestGiverComp;

	virtual FString InteractWith() override;


};
