
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

#include "ProjectDGameInstance.h"
#include "Characters/Components/InventoryComponent.h"
#include "Library/LevelManager.h"
#include "Pooling/SoundManager.h"
#include "Quest/AutoQuestAcceptActor.h"
#include "World/Trigger/DestructableWallActor.h"
#include "World/Trigger/TriggerBaseActor.h"

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
	LevelNames.Add( TEXT( "Tutorial" ) );
	LevelNames.Add( TEXT( "GameLv1" ) );
	LevelNames.Add( TEXT( "GameLv2" ) );
	LevelNames.Add( TEXT( "GameLv3" ) );

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComp" ) );

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
	
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FString CurLevelName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
	if (CurLevelName == LevelNames[0])
	{
		LevelIdx = 0;
		PlayerCameraboom = 1000.0f;
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
		ApplyAITxtP();
	}
	else if (CurLevelName == LevelNames[3])
	{
		LevelIdx = 3;
		PlayerCameraboom = 1200.0f;
		CreateLocationTitleWidget( LevelIdx );
		ApplyAITxtP();
	}
	else
	{
		LevelIdx = -1;
		PlayerCameraboom = 850.0f;
	}

	PlayBGMForLevel( LevelIdx );
	SetPlayerCameraboom( PlayerCameraboom );

	// Camera lerp settings
	if(PlayerCamCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction( this , FName( "HandleTimelineProgress" ) );
		TimelineComp->AddInterpFloat( PlayerCamCurve , ProgressFunction );

		FOnTimelineEvent TimelineFinishedFunction;
		TimelineFinishedFunction.BindUFunction( this , FName( "OnTimelineFinished" ) );
		TimelineComp->SetTimelineFinishedFunc( TimelineFinishedFunction );
	}

}

UAIConnectionLibrary* APlayerGameMode::GetAIConnectionLibrary() const
{
	return AIlib;
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
				SoundManager->PlayBGM( NewBGM, 0.1f );
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

	player->GetCameraBoom()->TargetArmLength = camboom ;
}

int32 APlayerGameMode::GetQuestID() const
{
	return questID;
}

void APlayerGameMode::SetQuestID( int32 NewQuestID )
{
	questID = NewQuestID;

}

FString APlayerGameMode::GetStringQuestID()
{
	return FStringQuestID;
}

void APlayerGameMode::SetStringQuestID(FString QuestID)
{
	FStringQuestID = QuestID;
}

void APlayerGameMode::TriggerQuest2004(FName CurrentquestID , bool queststatus)
{
	// 퀘스트 2003 완료 시, 자동으로 2004 퀘스트 받음
	for (TActorIterator<AAutoQuestAcceptActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		ActorItr->GiveQuest();
		AIlib->SendPImgToSrv( 2004 );
	}

	// Quest2004 생성 시, 벽 부숴지는 이벤트 발생
	for (TActorIterator<ADestructableWallActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		ActorItr->ExplosionWalls();
	}

}

void APlayerGameMode::StartGameStory()
{
	int32 index = 0;
	switch (LevelIdx)
	{
	case 0 : index = 0; break;
	case 1: index = 2; break;
	case 2: index = 0; break; // 스토리에 맞춰 수정할 예정
	case 3: index = 0; break; 
		default: break;
	}
	GI->ExecuteTutorial(EExplainType::MAIN_STORY, index);
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

void APlayerGameMode::ActiveLvTrigger()
{
	for (TActorIterator<ATriggerBaseActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		// Call the function on the actor
		ActorItr->ShowTrigger();
	}
}

void APlayerGameMode::LerpPlayerCameraLength(float TargetArmLength)
{
	auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
	if (player)
	{
		CameraBoom = player->GetCameraBoom();
		if (CameraBoom)
		{
			InitialArmLength = CameraBoom->TargetArmLength;
			NewTargetArmLength = TargetArmLength;

			TimelineComp->PlayFromStart();
		}
	}
}

void APlayerGameMode::HandleTimelineProgress(float Value)
{
	if (CameraBoom)
	{
		float Newcamlength = FMath::Lerp( InitialArmLength , NewTargetArmLength , Value );
		CameraBoom->TargetArmLength = Newcamlength;
	}
}

void APlayerGameMode::OnTimelineFinished()
{
}
