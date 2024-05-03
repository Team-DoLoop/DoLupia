// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterFSM.h"

#include "Components/CapsuleComponent.h"
#include "Monsters/Monster.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UMonsterFSM::UMonsterFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMonsterFSM::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AMonster>(GetOwner());
	
	state = EMonsterState::Patrol;
}


// Called every frame
void UMonsterFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case EMonsterState::Patrol:		PatrolState();		break;
	case EMonsterState::Move:		MoveState();		break;
	case EMonsterState::Attack:		AttackState();		break;
	case EMonsterState::Damage:		DamageState();		break;
	case EMonsterState::Die:		DieState();			break;
	}
}

void UMonsterFSM::PatrolState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UMonsterFSM::PatrolState()"));

	//플레이어를 타겟으로 설정
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	TargetVector = target->GetActorLocation() - me->GetActorLocation();
	if (TargetVector.Size() < TargetRange) {
		state = EMonsterState::Move;
	}
}

void UMonsterFSM::MoveState()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UMonsterFSM::MoveState()"));
	//플레이어 방향으로 이동
	MoveToTarget();
	if (TargetVector.Size() < AttackRange) {
		state = EMonsterState::Attack;
	}
}

void UMonsterFSM::AttackState()
{
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "UMonsterFSM::AttackState()" ) );

	MoveToTarget();

	if (TargetVector.Size() > AttackRange) {
		state = EMonsterState::Move;
	}
}

void UMonsterFSM::DamageState()
{
	GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "UMonsterFSM::DamageState()" ) );

	currentTime += GetWorld()->GetDeltaSeconds();
	if(currentTime > 1)
	{
		state = EMonsterState::Move;
		me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
		currentTime = 0;
	}

}

void UMonsterFSM::DieState()
{
	//죽음 애니메이션 끝난 후 destroy
	//me->Destroy();
}

void UMonsterFSM::MoveToTarget()
{
	TargetVector = target->GetActorLocation() - me->GetActorLocation();
	me->AddMovementInput( TargetVector.GetSafeNormal() );

	FRotator MonsterRotation = FRotationMatrix::MakeFromX( TargetVector ).Rotator();
	me->SetActorRotation( MonsterRotation );
}

void UMonsterFSM::TakeDamage()
{
	if (me->currentHP < 0)
	{
		me->currentHP = 0;
	}

	if (me->currentHP > 0)
	{
		state=EMonsterState::Damage;

		//뒤로 물러나기
	}

	else
	{
		state = EMonsterState::Die;
	}

	// 충돌체 끄기
	me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

