// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Lightning.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pooling/SoundManager.h"


void AFA_Blast_Lightning::BeginPlay()
{
	Super::BeginPlay();
	FloorAttackType = EFloorAttackType::BlastLightening;

	FTimerHandle Handle1;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle1 ,
		FTimerDelegate::CreateLambda( [this]()
			{
				CollisionStart();
			} ) ,
		1.0f , false
	);

	FTimerHandle Handle2;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle2 ,
		FTimerDelegate::CreateLambda( [this]()
			{
				if (DestroyTime > CurrentTime + 0.2f)
					UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );
			} ) ,
		0.05f, true
	);




	// UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnSecondEffect, GetActorLocation());
}

void AFA_Blast_Lightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator& CurrentRotation = GetActorRotation();
	const FRotator& NextRotation = UKismetMathLibrary::RLerp( CurrentRotation , FRotator(0.0, 0.0, 180.0), 0.125f, true);
	SetActorRotation( NextRotation );

	const FVector& CurrentScale = GetActorScale3D();

	if(CurrentScale.X <= 1.0)
		SetActorScale3D(CurrentScale + DeltaTime * 2.f);


	//UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );
}

void AFA_Blast_Lightning::Trigger()
{
	Super::Trigger();
}

void AFA_Blast_Lightning::CollisionEnd()
{
	UE_LOG( LogTemp , Warning , TEXT( "AFA_Blast_Fire::CollisionEnd()" ) );
	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );

	IgnoreActorsClear();

	FTimerHandle Handle;

	if(!IsPendingKillPending())
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			Handle ,
			FTimerDelegate::CreateLambda( [this]()
				{
					CollisionStart();
				} ) ,
			0.05f , false
		);
	}


}

void AFA_Blast_Lightning::CollisionStart()
{
	UE_LOG( LogTemp , Warning , TEXT( "AFA_Blast_Fire::CollisionStart()" ) );
	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );

	FTimerHandle Handle;

	if (!IsPendingKillPending())
	{
		GetWorld()->GetTimerManager().SetTimer
		(
			Handle ,
			FTimerDelegate::CreateLambda( [this]()
				{
					CollisionEnd();
				} ) ,
			0.05f , false
		);
	}
}


