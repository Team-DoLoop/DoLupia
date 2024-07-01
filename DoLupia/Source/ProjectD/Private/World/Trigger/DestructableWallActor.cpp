// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/DestructableWallActor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Components/BoxComponent.h"
#include "MovieSceneSequencePlayer.h"              
#include "MovieSceneSequencePlaybackSettings.h"     
#include "MovieSceneCommonHelpers.h"     
#include "ProjectDGameInstance.h"
#include "Animation/AnimTrace.h"
#include "Characters/ProjectDCharacter.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Pooling/SoundManager.h"

// Sets default values
ADestructableWallActor::ADestructableWallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestructableWallComp = CreateDefaultSubobject<UGeometryCollectionComponent>( TEXT( "DestructableWallComp" ) );
	RootComponent = DestructableWallComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	BoxComp->SetupAttachment( RootComponent );

	DestructableWallComp->SetSimulatePhysics( false );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );

	ExplosionVFX = CreateDefaultSubobject<UParticleSystemComponent>( TEXT( "ExplosionVFX" ) );
	ExplosionVFX->SetupAttachment( RootComponent );

	ExplosionVFX->bAutoActivate = false;

	SequencePlayer = CreateDefaultSubobject<ULevelSequencePlayer>( TEXT( "SequencePlayer" ) );
}

// Called when the game starts or when spawned
void ADestructableWallActor::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ASaveLoadObject::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	Target = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
	OriginalViewTarget = GetWorld()->GetFirstPlayerController()->GetViewTarget();
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	FFileHelper::SaveStringToFile( L"ASaveLoadObject::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void ADestructableWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableWallActor::ExplosionWalls( bool UseSequencer )
{
	if (!ExplosionSFX || !ExplosionVFX) return;

	if (UseSequencer)
	{
		Target->PlayerDoSomeThing( true );
		TriggerLvSequencer();

		// 벽폭발음
		ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( ExplosionSFX , ENPCSound::NPCSound2 , 0.1f );

		// 폭발 효과
		ExplosionVFX->ActivateSystem();
	}

	// 부숴지는 효과
	DestructableWallComp->SetSimulatePhysics( true );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void ADestructableWallActor::TriggerLvSequencer()
{
	if (!SequencePlayer) return;

	if (SequencePlayer && OriginalViewTarget)
	{
		UE_LOG( LogTemp , Log , TEXT( "Success to create Level Sequence Player." ) );
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend( OriginalViewTarget , 1.0f );
		SequencePlayer->Play();
	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "Failed to create Level Sequence Player." ) );
	}

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {
			SequencePlayer->Stop();  // 시퀀스 정지
			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend( Target , 1.0f );

			// 토토 시작
			GI->ExecuteTutorial(EExplainType::MAIN_STORY, -1, 9500);
		} ,
		5.0f , // 지연 시간(초)
		false
		);
}

