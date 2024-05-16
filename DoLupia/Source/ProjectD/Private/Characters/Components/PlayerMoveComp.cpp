// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerMoveComp.h"

#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/PlayerStateBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/KismetMathLibrary.h"

class AProjectDCharacter;
// Sets default values for this component's properties
UPlayerMoveComp::UPlayerMoveComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}


// Called when the game starts
void UPlayerMoveComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Player = Cast<AProjectDCharacter>(GetOwner());
	if(!Player) return;

	PlayerController = Cast<AProjectDPlayerController>(Player->GetController());
	PlayerFSM = Cast<UPlayerFSMComp>(Player->GetPlayerFSMComp());
	PlayerAnim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
	
}


// Called every frame
void UPlayerMoveComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// <---------------------- Move ---------------------->
void UPlayerMoveComp::OnSetDestinationTriggered()
{
	state = EPlayerState::MOVE;
	
	if(!Player) return;
	if(!PlayerFSM || !(PlayerFSM->CanChangeState(state))) return;
	
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	/*if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{*/
	bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	//}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = PlayerController->GetPawn();

	// switch player state
	// AProjectDCharacter* player = Cast<AProjectDCharacter>(GetCharacter());
	
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
		
		if(Player != nullptr && PlayerFSM->GetCurrentState() != EPlayerState::MOVE) PlayerFSM->ChangePlayerState(EPlayerState::MOVE);
	}
}

void UPlayerMoveComp::OnSetDestinationReleased()
{
	state = EPlayerState::MOVE;
	
	if(!Player) return;
	if(!PlayerFSM || !(PlayerFSM->CanChangeState(state))) return;
	
	// If it was a short press
	// if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(PlayerController, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(PlayerController, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}


// <---------------------- Evasion ---------------------->
void UPlayerMoveComp::Evasion()
{
	state = EPlayerState::EVASION;
	if(!Player || !PlayerController) return;
	if(!(PlayerFSM -> CanChangeState(state))) return;
	PlayerFSM -> ChangePlayerState(state);
	
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if(bHitSuccessful)
	{
		FVector EvasionVec = Hit.ImpactPoint - Player->GetActorLocation();
		Player->LaunchCharacter(EvasionVec.GetSafeNormal() * 10000, false, false);
		Player->SetActorRotation( UKismetMathLibrary::MakeRotFromXZ( EvasionVec , Player->GetActorUpVector() ) );
	}
	
	if(!PlayerAnim) return;
	PlayerAnim->PlayerEvasionAnimation();
}

void UPlayerMoveComp::EvasionEnd()
{
	if(!PlayerFSM) return;
	
	state = EPlayerState::IDLE;
	PlayerFSM->ChangePlayerState(state);
}


// <---------------------- Die ---------------------->
void UPlayerMoveComp::Die()
{
	state = EPlayerState::DIE;
	if(!(PlayerFSM->CanChangeState(state))) return;
	
	if(!PlayerFSM) return;
	PlayerFSM->ChangePlayerState(state);

	if(!PlayerAnim) return;
	PlayerAnim->PlayerDieAnimation();
}

