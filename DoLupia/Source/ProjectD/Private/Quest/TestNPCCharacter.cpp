// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/TestNPCCharacter.h"

#include "Quest/QuestGiver.h"

// Sets default values
ATestNPCCharacter::ATestNPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiverComp = CreateDefaultSubobject<UQuestGiver>( TEXT( "QuestGiverComp" ) );
}

// Called when the game starts or when spawned
void ATestNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FString ATestNPCCharacter::InteractWith()
{
	IQuestInteractionInterface::InteractWith();

	auto ObjectiveID = QuestGiverComp->InteractWith();
	return ObjectiveID;
}

