// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	AIlib = NewObject<UAIConnectionLibrary>();
	
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::NotifyActorBeginOverlap( AActor* OtherActor )
{
	AProjectDCharacter* player = Cast<AProjectDCharacter>( OtherActor );

	UE_LOG( LogTemp , Warning , TEXT( "NPC Test" ) );

	if (player)
	{
		gm->InitializeNPCConvWidget();
		UE_LOG( LogTemp , Warning , TEXT( "NPC - Overlap" ) );

		FString testStr = "이게 무슨 일이죠?";
		AIlib->SendNPCConversationToServer( testStr );

		UE_LOG( LogTemp , Warning , TEXT( "test : [%s]" ) , *gm->test )


	}
}

void ANPCBase::ReceiveNPCConv( FString conv )
{
	UE_LOG( LogTemp , Warning , TEXT( "conv : [%s]" ) , *conv )
}

