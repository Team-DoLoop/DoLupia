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
	ATestNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UQuestGiver* GetQuestGiver() const { return QuestGiverComp; };

	virtual FString InteractWith() override;

	virtual void LookAt() override;

private:
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	UQuestGiver* QuestGiverComp;
};
