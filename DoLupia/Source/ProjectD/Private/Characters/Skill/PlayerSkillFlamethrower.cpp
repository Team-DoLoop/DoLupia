// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillFlamethrower.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

APlayerSkillFlamethrower::APlayerSkillFlamethrower()
{
	PrimaryActorTick.bCanEverTick = true;

	FireEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireEffect"));
	FireEffectComponent->SetupAttachment(RootComponent);
	
	CurrentFireLength = 0.0f;
	FireSpeed = 10.0f;
	MaxFireLength = 2000.0f;
}

void APlayerSkillFlamethrower::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerSkillFlamethrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (FireEffectComponent && FireEffectComponent->IsActive())
	{
		CurrentFireLength += FireSpeed * DeltaTime;
		if (CurrentFireLength > MaxFireLength)
		{
			CurrentFireLength = MaxFireLength;
		}

		FVector MouseDirection = GetMouseDirection();
		FVector NewScale = FVector(MouseDirection.X, MouseDirection.Y, CurrentFireLength);
		FireEffectComponent->SetWorldLocation(NewScale);
	}
}

void APlayerSkillFlamethrower::StartFiring()
{
	if (FireEffect)
	{
		FireEffectComponent->SetTemplate(FireEffect);
		FireEffectComponent->ActivateSystem();

		CurrentFireLength = 0.0f;

		GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &APlayerSkillFlamethrower::ApplyDamage, 0.1f, true);
	}
}

void APlayerSkillFlamethrower::StopFiring()
{
	if (FireEffectComponent)
	{
		FireEffectComponent->DeactivateSystem();

		GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
	}
	CurrentFireLength = 0.0f;
}

void APlayerSkillFlamethrower::ApplyDamage()
{
	FVector StartLocation = GetActorLocation();
	FVector MouseDirection = GetMouseDirection();
	FVector EndLocation = StartLocation + MouseDirection * CurrentFireLength;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			UGameplayStatics::ApplyDamage(HitActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
}

FVector APlayerSkillFlamethrower::GetMouseDirection()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		FVector WorldLocation;
		FVector WorldDirection;
		if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		{
			FVector ActorLocation = GetActorLocation();
			WorldDirection.Z = 0; // Z축은 무시
			WorldDirection.Normalize();

			return WorldDirection;
		}
	}
	return FVector::ZeroVector;
}
