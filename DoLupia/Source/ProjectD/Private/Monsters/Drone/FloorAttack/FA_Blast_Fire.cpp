﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Fire.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"

void AFA_Blast_Fire::BeginPlay()
{
	Super::BeginPlay();

	FloorAttackType = EFloorAttackType::BlastFire;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );
	UNiagaraFunctionLibrary::SpawnSystemAtLocation( GetWorld() , SpawnSecondEffect , GetActorLocation() );

	FTimerHandle Handle;

	TWeakObjectPtr<AFA_Blast_Fire> WeakThis = this;

	FTimerDelegate TimerDel;
	TimerDel.BindLambda( [WeakThis]()
	{
	if (WeakThis.IsValid())
	{
		WeakThis->CollisionStart();
	}
	} );

	GetWorld()->GetTimerManager().SetTimer(Handle, TimerDel, 0.5f, false );

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

	if (!IsPendingKillPending())
	{
		FTimerHandle Handle;

		TWeakObjectPtr<AFA_Blast_Fire> WeakThis = this;

		if(AttackSphere)
			AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );

		IgnoreActorsClear();

		FTimerDelegate TimerDel;
		TimerDel.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->CollisionStart();
			}
		} );

		GetWorld()->GetTimerManager().SetTimer(Handle , TimerDel, 0.05f , false);
	}
}

void AFA_Blast_Fire::CollisionStart()
{
	UE_LOG( LogTemp , Warning , TEXT( "AFA_Blast_Fire::CollisionStart()" ) );
	AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );


	if (!IsPendingKillPending())
	{

		FTimerHandle Handle;

		TWeakObjectPtr<AFA_Blast_Fire> WeakThis = this;

		if (AttackSphere)
			AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );

		IgnoreActorsClear();

		FTimerDelegate TimerDel;
		TimerDel.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->CollisionEnd();
			}
		} );

		GetWorld()->GetTimerManager().SetTimer(Handle , TimerDel, 0.05f , false);
	}
}
