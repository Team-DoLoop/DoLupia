// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

class USoundBase;
class USoundCue;
class USoundWave;
class UAudioComponent;


UCLASS()
class PROJECTD_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static ASoundManager* GetInstance( UWorld* World );
	static void DestroyInstance();

	UFUNCTION( BlueprintCallable )
	void AddSound(USoundBase* Sound);

	void PlaySoundCue( USoundCue* SoundCue , FVector Location , float Volume = 1.f, float Pitch = 1.f);
	void PlaySoundCue2D( USoundCue* SoundCue ,  float Volume = 1.f, float Pitch = 1.f );
	void PlaySoundWave( USoundWave* SoundWave , FVector Location , float Volume, float Pitch = 1.f );
	void PlaySoundWave2D( USoundWave* SoundWave , float Volume = 1.f, float Pitch = 1.f);

	void PlayBGM( USoundBase* BGM );
	void StopBGM();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	ASoundManager();

	static ASoundManager* Instance;
	static FCriticalSection Mutex;
	//static FEvent* LockEvent;

	UPROPERTY( EditDefaultsOnly , Category = "Sound" )
	int32 InitialPoolSize;

	UPROPERTY()
	TArray<USoundBase*> SoundPool;

	UPROPERTY()
	TArray<USoundBase*> CurrentSound;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioBGM;

	UPROPERTY(EditAnywhere)
	USoundBase* CurrentBackgroundMusic;

};
