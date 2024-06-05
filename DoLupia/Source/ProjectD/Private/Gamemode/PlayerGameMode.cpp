
// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/PlayerGameMode.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/ProjectDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Library/AIConnectionLibrary.h"
#include "UserInterface/NPC/NPCConvWidget.h"
#include "UserInterface/Test/AITestWidget.h"
#include "AI/AITxtPlayer.h"
#include "Data/WidgetData.h"
#include "Engine.h"
#include "Items/Cape/PlayerCape.h"
#include <AI/AITxtBossAttack.h>
#include "Pooling/SoundManager.h"

APlayerGameMode::APlayerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectDPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass( TEXT( "/Game/Player/Blueprint/BP_Player" ) );
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass( TEXT( "/Game/TopDown/Blueprints/BP_TopDownPlayerController" ) );
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// Level
	LevelNames.Add( TEXT( "GameLv0" ) );
	LevelNames.Add( TEXT( "GameLv1" ) );
	LevelNames.Add( TEXT( "GameLv2" ) );
	LevelNames.Add( TEXT( "GameLv3" ) );
}

void APlayerGameMode::StartPlay()
{
	Super::StartPlay();

	// Get or create the AIConnectionLibrary instance
	AIlib = UAIConnectionLibrary::GetInstance( this );
}

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString CurLevelName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
	if (CurLevelName == LevelNames[0])
	{
		LevelIdx = 0;
	}
	else if (CurLevelName == LevelNames[1])
	{
		LevelIdx = 1;
	}
	else if (CurLevelName == LevelNames[2])
	{
		LevelIdx = 2;
	}
	else if (CurLevelName == LevelNames[3])
	{
		LevelIdx = 3;
	}
	else
	{
		LevelIdx = -1;
	}

	PlayBGMForLevel( LevelIdx );
}

UAIConnectionLibrary* APlayerGameMode::GetAIConnectionLibrary() const
{
	return AIlib;
}

void APlayerGameMode::InitializeNPCConvWidget()
{
	NPCConvUI = CreateWidget<UNPCConvWidget>( GetWorld() , NPCUIFactory );
	if (NPCConvUI)
	{
		NPCConvUI->AddToViewport(); 
	}
}

void APlayerGameMode::ReceiveNPCMsg( FString msg )
{
	NPCConvUI->SetupNPCConv( msg );
}

void APlayerGameMode::ApplyAITxtP()
{
	for (TActorIterator<APlayerCape> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		// Call the function on the actor
		ActorItr->UpdateActorMaterial();
	}
}

void APlayerGameMode::ApplyAITxtB()
{
	for (TActorIterator<AAITxtBossAttack> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		// Call the function on the actor
		ActorItr->UpdateActorMaterial();
	}
}

void APlayerGameMode::PlayBGMForLevel(int32 LvIndex)
{
	if (LvBGMs.Contains( LvIndex ))
	{
		if (USoundWave* NewBGM = LvBGMs[LvIndex])
		{
			if (ASoundManager* SoundManager = ASoundManager::GetInstance(GetWorld()))
			{
				SoundManager->PlayBGM( NewBGM );
				CurrentBGM = NewBGM;
			}
		}
	}
}

void APlayerGameMode::ChangeNextLv(FName LevelName)
{
	UGameplayStatics::OpenLevel( this , LevelName );
}
