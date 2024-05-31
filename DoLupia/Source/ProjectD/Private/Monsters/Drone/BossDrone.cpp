// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/BossDrone.h"

#include "Kismet/GameplayStatics.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Drone/BossDroneLaser.h"

ABossDrone::ABossDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	MuzzleOffSet = FVector(0.f, 0.f, 50.f);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drone Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	SetRootComponent( MeshComponent );
}

void ABossDrone::BeginPlay()
{
	Super::BeginPlay();

	Boss = Cast<ABossMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), ABossMonster::StaticClass()));
	Target = GetWorld()->GetFirstPlayerController()->GetCharacter();
	LaserActor = GetWorld()->SpawnActor<ABossDroneLaser>();
	LaserActor->Initialize(this);
}

void ABossDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Detect();
	Attack();

	switch (CurrentState)
	{
	case EDroneState::Following:
		FollowBoss( DeltaTime );
		break;
	case EDroneState::Attacking:

		break;
	case EDroneState::Returning:
		FollowBoss( DeltaTime );
		break;
	}

}

void ABossDrone::LaserOnGround( LaserOnGroundPattern Pattern, FVector Location )
{
	switch (Pattern)
	{
	case LaserOnGroundPattern::LOGP_Circle:
		
		break;

	case LaserOnGroundPattern::LOGP_Square:
		break;

	case LaserOnGroundPattern::LOGP_Star:
		break;
	}
}

void ABossDrone::FollowBoss(float DeltaTime)
{
	if (Boss)
	{
		FVector BossLocation = Boss->GetActorLocation();
		FVector Direction = (BossLocation - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction, MovementSpeed * DeltaTime);
	}
}

void ABossDrone::Detect() const
{
	if(LaserActor && Target)
		LaserActor->Initialize(Target->GetActorLocation() - GetActorLocation(), 3000.f);
}

void ABossDrone::Attack()
{
	if(LaserActor)
	{
		MuzzleStartLocation = GetActorLocation() + MuzzleOffSet;

		FVector TargetLocation = Target->GetActorLocation();

		SetActorRotation( (TargetLocation - MuzzleStartLocation).Rotation() );
		MuzzleEndLocation = TargetLocation + GetActorForwardVector() * AttackRange;
	}
}

void ABossDrone::ReturnToBoss()
{

}



