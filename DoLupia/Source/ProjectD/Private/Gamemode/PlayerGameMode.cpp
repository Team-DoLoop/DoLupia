﻿
// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/PlayerGameMode.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/ProjectDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Library/AIConnectionLibrary.h"
#include  "UserInterface/Event/LocationTitleWidget.h"
#include "Components/TextBlock.h"
#include "Data/WidgetData.h"
#include "Engine.h"
#include "Items/Cape/PlayerCape.h"
#include <AI/AITxtBossAttack.h>
#include "NPC/NPCBase.h"
#include "ProjectDGameInstance.h"
#include "Characters/Components/InventoryComponent.h"
#include "Library/LevelManager.h"
#include "Pooling/SoundManager.h"
#include "Quest/AutoQuestAcceptActor.h"
#include "Quest/MinigameQuestObject.h"
#include "World/Trigger/DestructableWallActor.h"
#include "World/Trigger/TriggerBaseActor.h"
#include <Quest/LocationMarker.h>

#include "Monsters/MonsterSpawnManager.h"

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

	//GameSaveManager->LoadGame( MyCharacter , ESaveType::SAVE_MAIN , "PlayerMainSave" );

	ASoundManager::GetInstance(GetWorld());
	ALevelManager::GetInstance(GetWorld());

}

void APlayerGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Player = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );

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
	InitializeSpawnerActors();

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
	Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	Player->GetCameraBoom()->TargetArmLength = camboom ;
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

FString APlayerGameMode::GetNxtQuestID() const
{
	return NextquestID;
}

void APlayerGameMode::SetNxtQuestID(FString nextquestID)
{
	UE_LOG( LogTemp , Error , TEXT( "gm - Next Quest ID: %s" ) , *nextquestID );
	NextquestID = nextquestID;

	FindNextNPC();
	FindMiniGame();
	if(NextquestID == "1003" || NextquestID == "2003" || NextquestID == "3001")
	{
		UE_LOG( LogTemp , Error , TEXT( "gm - FindMonsterSpawner" ) );
		FindMonsterSpawner( FName( *NextquestID ) , true );
	} else
	{
		FindMonsterSpawner( FName( *NextquestID ) , false );
	}
}

void APlayerGameMode::HandleIntrusionEvent()
{
	// 적의 침입
	// 카메라 관련 연출

	// 옆 통로로 갈 때, 카메라 각도 변경 트리거 활성화
	for (TActorIterator<ATriggerBaseActor> It( GetWorld() ); It; ++It)
	{
		ATriggerBaseActor* trigger = *It;

		// 다음 실행될 퀘스트랑 npc 퀘스트 같은지 확인
		if (trigger)
		{
			trigger->ActiveTriggerCollision();
		}
	}

	// 벽 부숴지는 효과
	for (TActorIterator<ADestructableWallActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		ActorItr->ExplosionWalls();
	}

	// 플레이어 카메라붐 각도 변경
	FRotator NewRotation = Player->GetCameraBoom()->GetRelativeRotation();
	NewRotation.Yaw = 180;
	Player->GetCameraBoom()->SetRelativeRotation( NewRotation );
}

void APlayerGameMode::StartGameStory()
{
	int32 index = 0;
	switch (LevelIdx)
	{
	case 0 : index = 0; break;
	case 1: index = 2; break;
	case 2: index = 4; break;
	case 3: index = 7; break; 
		default: break;
	}

	if(!IsToToNotInMapStart)
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
	Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
	if (Player)
	{
		CameraBoom = Player->GetCameraBoom();
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

void APlayerGameMode::InitializeSpawnerActors()
{
	SpawnerActors.Empty(); // 배열 비우기 (선택적)

	// 세계에서 스포너를 찾아서 배열에 추가
	for (TActorIterator<AMonsterSpawnManager> It( GetWorld() ); It; ++It)
	{
		SpawnerActors.Add( *It );
	}
}

void APlayerGameMode::FindNextNPC()
{
	for (TActorIterator<ANPCBase> It( GetWorld() ); It; ++It)
	{
		ANPCBase* NPC = *It;

		// 다음 실행될 퀘스트랑 npc 퀘스트 같은지 확인
		if (NPC && NPC->GetNxtQuestID() == NextquestID)
		{
			NPC->ChangeNPCColor( 4 ); 
			//return NPC;
		}
	}
	//return nullptr; // 해당 퀘스트 ID를 가진 NPC를 찾지 못한 경우
}

void APlayerGameMode::FindMiniGame()
{
	for (TActorIterator<AMinigameQuestObject> It( GetWorld() ); It; ++It)
	{
		AMinigameQuestObject* Minigame = *It;

		// 다음 실행될 퀘스트랑 npc 퀘스트 같은지 확인
		if (Minigame && Minigame->GetOwnQuestID() == NextquestID)
		{
			Minigame->ChangeMinigameColor( 3 );
			//return NPC;
		}
	}
}

void APlayerGameMode::FindMonsterSpawner( FName Tag , bool bActivate )
{
	for (AMonsterSpawnManager* Spawner : SpawnerActors)
	{
		// Check if the spawner's tag matches the specified Tag
		if (Spawner->Tags.Contains( Tag ))
		{
			// Activate or deactivate the spawner based on bActivate flag
			if (bActivate)
			{
				Spawner->ActiveMonsterSpawner();
			}
			else
			{
				Spawner->DeactiveMonsterSpawner();
			}
		}
	}
}

void APlayerGameMode::ActivateMarkers( int32 MarkerID )
{
	for (TActorIterator<ALocationMarker> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		ALocationMarker* Marker = *ActorItr;

		if (Marker && Marker->GetMarkerID() == MarkerID)
		{		
			//켜고 끄는 코드
			Marker->ActiveLocationMarker();
		}
	}
}


