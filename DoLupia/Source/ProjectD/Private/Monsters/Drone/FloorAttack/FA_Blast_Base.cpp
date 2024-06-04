// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Base.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pooling/SoundManager.h"

AFA_Blast_Base::AFA_Blast_Base()
{
}

void AFA_Blast_Base::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle ,
		FTimerDelegate::CreateLambda( [this]() { Trigger();}) ,
		1.f , false
	);
}

void AFA_Blast_Base::Trigger()
{
	Super::Trigger();

	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]()
	{
		PlayBlastSound();
		SpawnBlast();
	}));
}

void AFA_Blast_Base::PlayBlastSound()
{
	ASoundManager::GetInstance( GetWorld() )->PlaySoundWave( SpawnSound, GetActorLocation(), 1.f);
}

void AFA_Blast_Base::SpawnBlast()
{
	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle, 
		FTimerDelegate::CreateLambda([this]()
		{
			Destroy();
		}),
		1.f, false
	);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnEffect, GetActorLocation());
	// 이벤트 추가
}
