// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Drone/FloorAttack/FA_Blast_Base.h"

#include "NiagaraFunctionLibrary.h"
#include "Pooling/SoundManager.h"

AFA_Blast_Base::AFA_Blast_Base()
{
}

void AFA_Blast_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentTime += DeltaSeconds;
}

void AFA_Blast_Base::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AFA_Blast_Base::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer
	(
		Handle ,
		FTimerDelegate::CreateLambda( [this]() { Trigger();}) ,
		1.f , false
	);

	FFileHelper::SaveStringToFile( L"AFA_Blast_Base::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
	&IFileManager::Get() , ELogVerbosity::Log );
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
	ASoundManager::GetInstance( GetWorld() )->PlaySoundWave( SpawnSound , EMonsterSound::MonsterSound1, GetActorLocation(), 0.1f);
}

void AFA_Blast_Base::SpawnBlast()
{

	FTimerHandle Handle;

	TWeakObjectPtr<AFA_Blast_Base> WeakThis = this;

	FTimerDelegate TimerDel;
	TimerDel.BindLambda( [WeakThis]()
	{
	if (WeakThis.IsValid())
	{
		WeakThis->Test_Destoty();
	}
	} );

	GetWorld()->GetTimerManager().SetTimer( Handle , TimerDel , DestroyTime , false );

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnEffect, GetActorLocation());
	// 이벤트 추가
}

void AFA_Blast_Base::Test_Destoty()
{
	UE_LOG(LogTemp, Warning, TEXT("AFA_Blast_Base::Test_Destoty()"));
	Destroy();
}
