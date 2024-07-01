// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Lightning.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pooling/SoundManager.h"


void AFA_Blast_Lightning::BeginPlay()
{
	Super::BeginPlay();


	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AFA_Blast_Lightning::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	FloorAttackType = EFloorAttackType::BlastLightening;

	TWeakObjectPtr<AFA_Blast_Lightning> WeakThis = this;

	FTimerHandle Handle1;
	FTimerDelegate TimerDel1;

	if (!IsPendingKillPending())
	{

		TimerDel1.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->CollisionStart();
			}
		} );

		GetWorld()->GetTimerManager().SetTimer(Handle1 , TimerDel1 , 1.0f , false);

		FTimerHandle Handle2;
		FTimerDelegate TimerDel2;

		TimerDel2.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				if (WeakThis->DestroyTime > WeakThis->CurrentTime + 0.2f)
					UNiagaraFunctionLibrary::SpawnSystemAtLocation( WeakThis->GetWorld() , WeakThis->SpawnSecondEffect , WeakThis->GetActorLocation() );
			}
		} );

		GetWorld()->GetTimerManager().SetTimer(Handle2 , TimerDel2, 0.05f, true);
	}
	else
	{
		FFileHelper::SaveStringToFile( L"AFA_Blast_Lightning::BeginPlay -> IsPendingKillPending" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
	}


	FFileHelper::SaveStringToFile( L"AFA_Blast_Lightning::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

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

	if (!IsPendingKillPending())
	{
		FTimerHandle Handle;


		TWeakObjectPtr<AFA_Blast_Lightning> WeakThis = this;

		FTimerDelegate TimerDel;
		TimerDel.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->CollisionStart();
			}
		} );

		GetWorld()->GetTimerManager().SetTimer( Handle , TimerDel , 0.05f , false );

		IgnoreActorsClear();

		if (AttackSphere)
			AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::NoCollision );
	}
}

void AFA_Blast_Lightning::CollisionStart()
{

	if (!IsPendingKillPending())
	{
		FTimerHandle Handle;

		TWeakObjectPtr<AFA_Blast_Lightning> WeakThis = this;

		FTimerDelegate TimerDel;
		TimerDel.BindLambda( [WeakThis]()
		{
			if (WeakThis.IsValid())
			{
				WeakThis->CollisionEnd();
			}
		} );

		GetWorld()->GetTimerManager().SetTimer( Handle , TimerDel , 0.05f , false );

		IgnoreActorsClear();

		if (AttackSphere)
			AttackSphere->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );
	}
}


