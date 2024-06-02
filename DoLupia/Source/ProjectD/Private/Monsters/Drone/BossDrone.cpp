// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/BossDrone.h"

#include "Kismet/GameplayStatics.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Drone/BossDroneLaser.h"

ABossDrone::ABossDrone()
{
	PrimaryActorTick.bCanEverTick = true;

	MuzzleOffSet = FVector(0.f, 0.f, 50.f);

	DroneMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drone Mesh"));
	DroneMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	DroneMeshComponent->SetVisibility(true);

	OrbitRadius = 300.0f;
	OrbitSpeed = 50.0f;
	CurrentAngle = 0.0f;

	SetRootComponent( DroneMeshComponent );


}

void ABossDrone::BeginPlay()
{
	Super::BeginPlay();

	Boss = Cast<ABossMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), ABossMonster::StaticClass()));
	Target = GetWorld()->GetFirstPlayerController()->GetCharacter();
	LaserActor = GetWorld()->SpawnActor<ABossDroneLaser>(LaserFactory);
	LaserActor->Initialize(this);
}

void ABossDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 각도를 시간에 따라 증가
	CurrentAngle += OrbitSpeed * DeltaTime;

	//Detect();
	//Attack();

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
		//FVector BossLocation = Boss->GetActorLocation() + BossIntervalLocation;
		FVector Direction = (Boss->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		// 각도 값을 라디안으로 변환
		float RadianAngle = FMath::DegreesToRadians( CurrentAngle );

		// 새로운 위치 계산
		FVector NewLocation;
		NewLocation.X = Boss->GetActorLocation().X + BossIntervalLocation.X + OrbitRadius * FMath::Cos( RadianAngle );
		NewLocation.Y = Boss->GetActorLocation().Y + BossIntervalLocation.Y + OrbitRadius * FMath::Sin( RadianAngle );
		NewLocation.Z = Boss->GetActorLocation().Z + BossIntervalLocation.Z;

		SetActorLocation( NewLocation );

		//SetActorLocation( FMath::Lerp( GetActorLocation() , Boss->GetActorLocation() + BossIntervalLocation , 0.1f ) );
		////AddMovementInput(Direction, MovementSpeed * DeltaTime);
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



