// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UPlayerAttackComp::UPlayerAttackComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerAttackComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerAttackComp::SetUpInput(UEnhancedInputComponent* input)
{
	if(input == nullptr) return;

	input->BindAction(iaAttack, ETriggerEvent::Started, this, &UPlayerAttackComp::OnIaAttack);
}

void UPlayerAttackComp::OnIaAttack(const FInputActionValue& value)
{
	
}

