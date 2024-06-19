// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/DestructableWallActor.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
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

	/*
	static ConstructorHelpers::FObjectFinder<ULevelSequence> ExplosionSeqAsset( TEXT( "LevelSequence'/Game/Sequencer/Lv2ExplosionSeq.Lv2ExplosionSeq'" ) );
	if (ExplosionSeqAsset.Succeeded())
	{
		ExplosionSeq = ExplosionSeqAsset.Object;
	}
	else
	{
		return;
	}
	*/

	//ExplosionSeq = LoadObject<ULevelSequence>( nullptr , TEXT( "/Game/Sequencer/Lv2ExplosionSeq.Lv2ExplosionSeq" ) );
}

// Called when the game starts or when spawned
void ADestructableWallActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADestructableWallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructableWallActor::ExplosionWalls()
{
	if (!ExplosionSFX || !ExplosionVFX) return;

	// Load the Level Sequence
	//ULevelSequence* ExplosionSequence = LoadObject<ULevelSequence>( nullptr , TEXT( "/Game/Sequencer/Lv2ExplosionSeq.Lv2ExplosionSeq" ) );
	/*
	if (!ExplosionSeq) return;

	// Create a Level Sequence Player
	FMovieSceneSequencePlaybackSettings PlaybackSettings;
	ALevelSequenceActor* LevelSequenceActor = nullptr;
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld() , ExplosionSeq , PlaybackSettings, LevelSequenceActor );

	if (SequencePlayer)
	{
		SequencePlayer->Play();
	}
	*/

	// 벽폭발음
	ASoundManager::GetInstance( GetWorld() )->PlaySoundWave2D( ExplosionSFX , ENPCSound::NPCSound2 , 0.1f );

	// 폭발 효과
	ExplosionVFX->ActivateSystem();

	UE_LOG( LogTemp , Warning , TEXT( "Destroy Walls" )  )

	// 부숴지는 효과
	DestructableWallComp->SetSimulatePhysics( true );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

