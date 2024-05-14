// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerFSMComp.h"

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

	CheckState(CurrentState);
}

void UPlayerFSMComp::CheckState(EPlayerState _state)
{
	switch (_state)
	{
	case EPlayerState::IDLE:				return;
	case EPlayerState::MOVE:	TickMove();	return;
	case EPlayerState::EVASION:				return;
		
	case EPlayerState::ATTACK:				return;
	case EPlayerState::DAMAGE:				return;

	case EPlayerState::TALK_NPC:			return;
		
	case EPlayerState::DIE:					return;
	}
}

void UPlayerFSMComp::ChangePlayerState(EPlayerState _state)
{
	if(!CanChangeState(_state)) return;
	
	CurrentState = _state;
	UE_LOG(LogTemplatePlayerFSM, Log, TEXT("ChangePlayerState : %s"), *UEnum::GetValueAsName(_state).ToString());
}

// 현재 상태, 바뀔 상태
bool UPlayerFSMComp::CanChangeState(EPlayerState _changeState)
{
	// if(CurrentState == _changeState) return false;
	switch (_changeState)
	{
	case EPlayerState::IDLE : return  true;
	case EPlayerState::MOVE : return CanMoveState(CurrentState);

	case EPlayerState::ATTACK : return CanAttackState(CurrentState);
	case EPlayerState::DAMAGE : return CanDamageState(CurrentState);
	case EPlayerState::EVASION : return CanEvasionState(CurrentState);
		
	case EPlayerState::TALK_NPC : return CanTalkNPCState(CurrentState);

	case EPlayerState::DIE : return CanDieState(CurrentState);
	}

	return false;
}


// <--------------------- Move --------------------->

void UPlayerFSMComp::TickMove()
{
	if((PlayerMovement->GetCurrentAcceleration() == FVector(0))&& UKismetMathLibrary::VSizeXY(PlayerMovement->Velocity)<= 3.0f)
	{
		ChangePlayerState(EPlayerState::IDLE);
	}
}

bool UPlayerFSMComp::CanMoveState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 공격, 회피, 대화, 죽음
	switch (_CurrentState)
	{
	case EPlayerState::ATTACK : return false;
	case EPlayerState::EVASION : return false;

	case EPlayerState::TALK_NPC : return false;
		
	case EPlayerState::DIE : return false;
	}

	return true;
}


// <--------------------- Evasion --------------------->

bool UPlayerFSMComp::CanEvasionState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 회피, 대화, 죽음
	switch (_CurrentState)
	{
	case EPlayerState::EVASION : return false;
	case EPlayerState::TALK_NPC : return false;
		
	case EPlayerState::DIE : return false;
	}
	return true;
}


// <--------------------- Attack --------------------->

bool UPlayerFSMComp::CanAttackState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 공격, 회피, 대화, 죽음
	switch (_CurrentState)
	{
	case EPlayerState::ATTACK : return false;
	case EPlayerState::EVASION : return false;

	case EPlayerState::TALK_NPC : return false;
		
	case EPlayerState::DIE : return false;
	}

	return true;
}


// <--------------------- Damage --------------------->

bool UPlayerFSMComp::CanDamageState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 회피, 대화, 죽음
	switch (_CurrentState)
	{
	case EPlayerState::EVASION : return false;

	case EPlayerState::TALK_NPC : return false;
	case EPlayerState::DIE : return false;
	}
	return true;
}


// <--------------------- TalkNPC --------------------->

bool UPlayerFSMComp::CanTalkNPCState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 회피, 죽음
	switch (_CurrentState)
	{
	case EPlayerState::EVASION : return false;
	case EPlayerState::DIE : return false;
	}
	return true;
}


// <--------------------- Die --------------------->

bool UPlayerFSMComp::CanDieState(EPlayerState _CurrentState)
{
	// 안되는 상태 : 죽음
	 switch (_CurrentState)
	{
	 	case EPlayerState::DIE : return false;
		
	}

	return true;
}
