// Fill out your copyright notice in the Description page of Project Settings.


#include "Pooling/SoundManager.h"

#include "AssetTypeActions/AssetDefinition_SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundWave.h"

ASoundManager* ASoundManager::Instance = nullptr;
FCriticalSection ASoundManager::Mutex;
//FEvent* ASoundManager::LockEvent = FPlatformProcess::CreateSynchEvent( true );

ASoundManager::ASoundManager()
{
	PrimaryActorTick.bCanEverTick = false;
	//InitialPoolSize = 10;

	AudioBGM = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio BGM"));
}


void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	PlayBGM( CurrentBackgroundMusic );

}

void ASoundManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 게임이 종료될 때 사운드 매니저 인스턴스를 삭제
	ASoundManager::DestroyInstance();
}

ASoundManager* ASoundManager::GetInstance(UWorld* World)
{

	if (Instance == nullptr)
	{
		Instance = World->SpawnActor<ASoundManager>();
	}

	return Instance;
}

void ASoundManager::DestroyInstance()
{
	if (Instance)
	{
		Instance->RemoveFromRoot(); // GC 해제
		Instance->Destroy();
		Instance = nullptr;
	}
}

void ASoundManager::AddSound(USoundBase* Sound)
{
	if(Sound)
	{
		SoundPool.AddUnique(Sound);
	}
}

void ASoundManager::PlaySoundCue(USoundCue* SoundCue, FVector Location, float Volume, float Pitch )
{
	if(SoundCue)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundCue, Location, Volume, Pitch );
	}
}

void ASoundManager::PlaySoundCue2D(USoundCue* SoundCue, float Volume, float Pitch )
{
	if (SoundCue)
	{
		UGameplayStatics::PlaySound2D( this , SoundCue, Volume , Pitch );
	}
}

void ASoundManager::PlaySoundWave(USoundWave* SoundWave, FVector Location, float Volume, float Pitch )
{
	if(SoundWave)
	{
		UGameplayStatics::PlaySoundAtLocation( this , SoundWave , Location, Volume, Pitch );
	}
}

void ASoundManager::PlaySoundWave2D(USoundWave* SoundWave, float Volume, float Pitch)
{
	if (SoundWave)
	{
		UGameplayStatics::PlaySound2D( this , SoundWave, Volume, Pitch );
	}
}

void ASoundManager::PlayBGM(USoundBase* BGM)
{
	if(CurrentBackgroundMusic)
		StopBGM();

	CurrentBackgroundMusic = BGM;
	
	AudioBGM->SetSound( CurrentBackgroundMusic );
	AudioBGM->Play();
}


void ASoundManager::StopBGM()
{
	if (CurrentBackgroundMusic)
	{
		AudioBGM->Stop();
		AudioBGM->SetSound( nullptr );
	}
}



