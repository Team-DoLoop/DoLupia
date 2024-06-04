// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Quest/QuestInteractionInterface.h"
#include "NPCBase.generated.h"

class UWidgetComponent;
class UDialogComponent;
class UQuestGiver;
class UNPCAnim;
class APlayerGameMode;
class UAIConnectionLibrary;


UCLASS()
class PROJECTD_API ANPCBase : public ACharacter , public IQuestInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;

private:
	UPROPERTY()
	UNPCAnim* anim;

	UPROPERTY()
	APlayerGameMode* gm;

	UPROPERTY()
	UAIConnectionLibrary* AIlib;

	/*-----------  AI Chatbot 연동  -----------*/
private:
	FString NPCConversation;

	//Player 상호작용 시 호출
	void BeginChat();

	UFUNCTION()
	void CallNPCMessageDelegate( FString Message );

	/*-----------  Dialog Component  -----------*/
public:
	void DialogWith();

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dialog" )
	int32 DialogNum;

	UPROPERTY( BlueprintReadWrite , EditAnywhere , Category = "Dialog" )
	FString NPCID;

private:
	UPROPERTY( VisibleAnywhere , Category = "Dialog" )
	UDialogComponent* DialogComp;

	/*-----------  Quest Component  -----------*/
public:
	FORCEINLINE UQuestGiver* GetQuestGiver() const { return QuestGiverComp; };
	virtual FString InteractWith() override;
	virtual void LookAt() override;

private:
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	UQuestGiver* QuestGiverComp;

	/*---------------------- Post Process Depth ------------------*/
public:
	int32 stencilDepth = 4 ;

private:
	void ChangeNPCStatus( int32 depth );


};
