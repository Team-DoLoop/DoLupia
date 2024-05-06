// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PlayerAttackComp.h"

#include "EnhancedInputComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/PlayerFSMComp.h"

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
	Player = Cast<AProjectDCharacter>(GetOwner());
	if(!Player) return;
	PlayerFSMComp = Player->GetPlayerFSMComp();
	PlayerAnim = Cast<UPlayerAnimInstance>(Player->GetMesh()->GetAnimInstance());
}


// Called every frame
void UPlayerAttackComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerAttackComp::Attack()
{
	if(!PlayerFSMComp) return;
	PlayerFSMComp->ChangePlayerState(EPlayerState::ATTACK);

	if(!PlayerAnim) return;
	PlayerAnim->PlayerAttackAnimation();
}

