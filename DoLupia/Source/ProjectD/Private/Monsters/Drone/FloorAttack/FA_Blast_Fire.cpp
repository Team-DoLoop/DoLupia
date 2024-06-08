// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Fire.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"

void AFA_Blast_Fire::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );
	UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle,
		FTimerDelegate::CreateLambda( [this]() 
		{ 
				CollisionStart();
		}),
		0.5f, false 
	);

}

void AFA_Blast_Fire::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFA_Blast_Fire::Trigger()
{
	Super::Trigger();
}

void AFA_Blast_Fire::CollisionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("AFA_Blast_Fire::CollisionEnd()"));
	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );

	IgnoreActorsClear();

	FTimerHandle Handle;

	if (!IsPendingKillPending())
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

void AFA_Blast_Fire::CollisionStart()
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
