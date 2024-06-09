// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerMoveComp.h"

#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Characters/PlayerStateBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Data/WidgetData.h"
#include "Kismet/KismetMathLibrary.h"
#include "UserInterface/Event/PlayerDieWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/Skill/PlayerEvasionSlotWidget.h"

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
	
	float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimerHandle);
	Player->GetPlayerDefaultsWidget()->GetPlayerBattleWidget()->GetPlayerEvasionSlotUI()->UpdateEvasionCoolTimeUI(GetCooldownPercent(RemainingTime, EvasionCoolTime) );
}

float UPlayerMoveComp::GetCooldownPercent(float RemainingTime, float _SkillCoolTime)
{
	if (_SkillCoolTime > 0)
	{
		return  (RemainingTime / _SkillCoolTime);
	}
	
	return 0.0f;
}


// <---------------------- Move ---------------------->
void UPlayerMoveComp::OnSetDestinationTriggered()
{
	state = EPlayerState::MOVE;
	
	if(!Player) return;
	if(!PlayerFSM || !(PlayerFSM->CanChangeState(state))) return;
	if(PlayerFSM->GetCurrentState() != state) PlayerFSM->ChangePlayerState(state);

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	FVector WorldDirection = (CachedDestination - Player->GetActorLocation()).GetSafeNormal();
	Player->AddMovementInput(WorldDirection, 1.0, false);
	
}

void UPlayerMoveComp::OnSetDestinationReleased()
{
	state = EPlayerState::MOVE;
	if(!Player) return;
	if(!PlayerFSM || !(PlayerFSM->CanChangeState(state))) return;
	if(PlayerFSM->GetCurrentState() != state) PlayerFSM->ChangePlayerState(state);
	
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
	if(GetWorld()->GetTimerManager().IsTimerActive(CooldownTimerHandle)) return;
	state = EPlayerState::EVASION;
	if(!Player || !PlayerController) return;
	if(!(PlayerFSM -> CanChangeState(state))) return;
	PlayerFSM -> ChangePlayerState(state);
	
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if(bHitSuccessful)
	{
		FVector EvasionVec = Hit.ImpactPoint - Player->GetActorLocation();
		EvasionVec.Z = 0.0f;
		
		FRotator TargetRot = UKismetMathLibrary::MakeRotFromXZ(EvasionVec, Player->GetActorUpVector());
		FRotator PlayerRot = Player->GetActorRotation();
		FRotator TempRot = FRotator(PlayerRot.Pitch, TargetRot.Yaw, PlayerRot.Roll);

		Player->LaunchCharacter(EvasionVec.GetSafeNormal() * EvasionRange, false, false);
		Player->SetActorRotation( TempRot );
	}
	
	if(!PlayerAnim) return;
	PlayerAnim->PlayerEvasionAnimation();

	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, EvasionCoolTime, false);
}

void UPlayerMoveComp::EvasionEnd()
{
	if(!PlayerFSM) return;
	
	state = EPlayerState::IDLE;
	PlayerFSM->ChangePlayerState(state);
}


// <---------------------- Die ------------------>
void UPlayerMoveComp::Die()
{
	if(!PlayerController || !PlayerFSM) return;
	PlayerController->StopMovement();
	
	state = EPlayerState::DIE;
	if(!(PlayerFSM->CanChangeState(state))) return;
	PlayerFSM->ChangePlayerState(state);

	if(!PlayerAnim) return;
	PlayerAnim->PlayerDieAnimation();

	if(!PlayerDieUI && PlayerDieUIFactory)
	{
		PlayerDieUI = CreateWidget<UPlayerDieWidget>(GetWorld(), PlayerDieUIFactory);
		PlayerDieUI->AddToViewport(static_cast<int32>(ViewPortPriority::Main));
	}
	
}

