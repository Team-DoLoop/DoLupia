// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerFSMComp.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "VisualLogger/VisualLoggerTypes.h"


DEFINE_LOG_CATEGORY(LogTemplatePlayerFSM);

// Sets default values for this component's properties
UPlayerFSMComp::UPlayerFSMComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFSMComp::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AProjectDCharacter>(GetOwner());
	if(Player != nullptr)
	{
		PlayerMovement = Player->GetCharacterMovement();
		PlayerController = Cast<AProjectDPlayerController>(Player->GetController());
	}
	
	CurrentState = EPlayerState::IDLE;
}


// Called every frame
void UPlayerFSMComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// State - Move

	if(PlayerMovement == nullptr) return;

	if(CurrentState == EPlayerState::MOVE && (PlayerMovement->GetCurrentAcceleration() == FVector(0))&& UKismetMathLibrary::VSizeXY(PlayerMovement->Velocity)<= 3.0f)
	{
		ChangePlayerState(EPlayerState::IDLE);
	}
}

void UPlayerFSMComp::ChangePlayerState(EPlayerState _state)
{
	if(CurrentState == _state) return;
	
	CurrentState = _state;
	UE_LOG(LogTemplatePlayerFSM, Log, TEXT("ChangePlayerState : %s"), *UEnum::GetValueAsName(_state).ToString());
}

