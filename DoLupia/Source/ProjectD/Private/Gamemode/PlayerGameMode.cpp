
// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/PlayerGameMode.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/ProjectDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Library/AIConnectionLibrary.h"
#include "UserInterface/NPC/NPCConvWidget.h"
#include "UserInterface/Test/AITestWidget.h"
#include  "UserInterface/Event/LocationTitleWidget.h"
#include "Components/TextBlock.h"
#include "AI/AITxtPlayer.h"
#include "Data/WidgetData.h"
#include "Engine.h"
#include "Items/Cape/PlayerCape.h"
#include <AI/AITxtBossAttack.h>

#include "Characters/Components/InventoryComponent.h"
#include "Library/LevelManager.h"
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

	//AProjectDCharacter* MyCharacter = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );

	//GameSaveManager->LoadGame( MyCharacter , ESaveType::SAVE_MAIN , "PlayerMainSave" );

	ASoundManager::GetInstance(GetWorld());
	ALevelManager::GetInstance(GetWorld());

}

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	FString CurLevelName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
	if (CurLevelName == LevelNames[0])
	{
		LevelIdx = 0;
		//PlayerCameraboom = 1000.0f;
	}
	else if (CurLevelName == LevelNames[1])
	{
		LevelIdx = 1;
		PlayerCameraboom = 1000.0f;
		CreateLocationTitleWidget( LevelIdx );
	}
	else if (CurLevelName == LevelNames[2])
	{
		LevelIdx = 2;
		PlayerCameraboom = 700.0f;
		CreateLocationTitleWidget( LevelIdx );
	}
	else if (CurLevelName == LevelNames[3])
	{
		LevelIdx = 3;
		PlayerCameraboom = 1200.0f;
		CreateLocationTitleWidget( LevelIdx );
	}
	else
	{
		LevelIdx = -1;
		PlayerCameraboom = 850.0f;
	}

	PlayBGMForLevel( LevelIdx );
	SetPlayerCameraboom( PlayerCameraboom );
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
				SoundManager->PlayBGM( NewBGM, 0.2 );
				CurrentBGM = NewBGM;
			}
		}
	}
}

void APlayerGameMode::ChangeNextLv(FName LevelName, AProjectDCharacter* Character, ESaveType SaveType)
{
	SAVE( Character, SaveType, "PlayerMainSave" , "PlayerMainSave", LevelName, false, false);

	//ALevelManager::GetInstance(GetWorld())->SaveGame( Character, SaveType, "PlayerMainSave", "PlayerMainSave", LevelName, 
	//	Character->GetActorLocation(), Character->GetInventory()->GetInventoryContents(), false, false);

	UGameplayStatics::OpenLevel( this , LevelName );
}

void APlayerGameMode::SetPlayerCameraboom(float camboom)
{
	// Player Load
	auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	// 플레이어 쪽에서 카메라 설정값 셋팅하는 함수나, camera 변수 public 으로 바꿔줘야 겜모에서 변경 가능
	player->CameraBoom->TargetArmLength = camboom ;
}

int32 APlayerGameMode::GetQuestID() const
{
	return questID;
}

void APlayerGameMode::SetQuestID(int32 NewQuestID )
{
	questID = NewQuestID;
	
}

void APlayerGameMode::CreateLocationTitleWidget( int32 currentlevel )
{
	if (LocationFactory)
	{
		ULocationTitleWidget* LocationWidget = CreateWidget<ULocationTitleWidget>( GetWorld() , LocationFactory );

		if (LocationWidget)
		{
			FText LocationName;
			switch (currentlevel)
			{
			case 1:
				LocationName = FText::FromString( TEXT( "길거리" ) );
				break;
			case 2:
				LocationName = FText::FromString( TEXT( "혁명군 기지" ) );
				break;
			case 3:
				LocationName = FText::FromString( TEXT( "보스 기지" ) );
				break;
			default:
				LocationName = FText::FromString( TEXT( "Unknown Location" ) );
				break;
			}
			LocationWidget->txt_LocationName->SetText( LocationName );
			LocationWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Default) );

		}
	}
}
