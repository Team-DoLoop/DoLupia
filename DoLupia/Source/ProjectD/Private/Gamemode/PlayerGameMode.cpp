
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
#include "Quest/MinigameQuestObject.h"
#include "World/Trigger/DestructableWallActor.h"
#include "World/Trigger/TriggerBaseActor.h"
#include <Quest/LocationMarker.h>

#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h" 
#include "Monsters/BossMonster.h"
#include "Monsters/MonsterSpawnManager.h"
#include "UserInterface/Ending/EndingCreditsWidget.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"

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
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass( TEXT( "/Game/Player/Input/BP_TopDownPlayerController" ) );
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// Add Levels Name
	LevelNames.Add( TEXT( "Opening" ) );
	LevelNames.Add( TEXT( "Tutorial" ) );
	LevelNames.Add( TEXT( "GameLv1" ) );
	LevelNames.Add( TEXT( "GameLv2" ) );
	LevelNames.Add( TEXT( "GameLv3" ) );

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComp" ) );
	Lv3SequencePlayer = CreateDefaultSubobject<ULevelSequencePlayer>( TEXT( "Lv3SequencePlayer" ) );
	bossComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "bossComp" ) );
	playerComp = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "playerComp" ) );


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
		LevelIdx = 999;
		IsToToNotInMapStart = true;
		//if (Player)
		//{
		//	Player->Destroy();
		//	Player = nullptr;
		//}
	}
	else if (CurLevelName == LevelNames[1])
	{
		LevelIdx = 0;
		PlayerCameraboom = 1000.0f;

	}
	else if (CurLevelName == LevelNames[2])
	{
		LevelIdx = 1;
		PlayerCameraboom = 1000.0f;
		CreateLocationTitleWidget( LevelIdx );

		// 재시작 시, 인스턴스에 저장된 퀘스트ID별로 분기
		// 처음 맵1 시작이면 변경 X, 재시작으로 맵1 시작이면 빨간색
		if (GI->CompletedQuests.Contains( "1002" ))
		{
			ApplyAITxtP( 1 );
		}
		if (GI->CompletedQuests.Contains( "1003" )) {
			ActiveLvTrigger();
		}
		
	}
	else if (CurLevelName == LevelNames[3])
	{
		LevelIdx = 2;
		PlayerCameraboom = 700.0f;
		CreateLocationTitleWidget( LevelIdx );

		// 재시작하는 걸 알 수 있는 인자값 필요
		// 처음 맵2 시작이면 빨간색, 재시작으로 맵2 시작이면 노란색
		if(GI->CompletedQuests.Contains("2004"))
		{
			ApplyAITxtP( 3 );
		} else if(GI->CompletedQuests.Contains( "2002" ))
		{
			ApplyAITxtP( 2 );
		}
		else
		{
			ApplyAITxtP( 1 );
		}
		if (GI->CompletedQuests.Contains( "3001" )) {
			ActiveLvTrigger();
		}
		
	}
	else if (CurLevelName == LevelNames[4])
	{
		LevelIdx = 3;
		PlayerCameraboom = 1200.0f;
		CreateLocationTitleWidget( LevelIdx );

		ApplyAITxtP( LevelIdx );
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

	// Camera Sequencer
	Target = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
	OriginalViewTarget = GetWorld()->GetFirstPlayerController()->GetViewTarget();
}

UAIConnectionLibrary* APlayerGameMode::GetAIConnectionLibrary() const
{
	return AIlib;
}

void APlayerGameMode::ApplyAITxtP( int32 Lvindex )
{
	for (TActorIterator<APlayerCape> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		// Call the function on the actor
		ActorItr->UpdateActorMaterial( Lvindex );
	}
}

void APlayerGameMode::ApplyAITxtB( FString _Attacktype )
{
	for (TActorIterator<AAITxtBossAttack> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		// Call the function on the actor
		ActorItr->UpdateActorMaterial( _Attacktype );
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

void APlayerGameMode::ChangeNextLv(FName LevelName, AProjectDCharacter* Character, ESaveType SaveType, bool OpenLevel)
{
	SAVE( Character , ESaveType::SAVE_MAIN , "PlayerMainSave" , "PlayerMainSave" , LevelName , false );

	if(OpenLevel)
		UGameplayStatics::OpenLevel( this , LevelName );
}

void APlayerGameMode::SetPlayerCameraboom(float camboom)
{
	// Player Load
	if(Player)
	{
		Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
		Player->GetCameraBoom()->TargetArmLength = camboom;
	}
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

FString APlayerGameMode::GetNxtQuestTag() const
{
	return NextquestTag;
}

void APlayerGameMode::SetNxtCompleteQuestTag(FString nextquesttag)
{
	UE_LOG( LogTemp , Error , TEXT( "gm - Next Quest Tag: %s" ) , *nextquesttag );
	NextquestTag = nextquesttag;

	// Quest Complete -> NPC, Spawner Active
	OnNextNPCQuestTagReceived.Broadcast( NextquestTag );
	OnNextSpawnerQuestTagCompleted.Broadcast();
}

void APlayerGameMode::SetNxtReceiveQuestTag(FString nextquesttag)
{
	UE_LOG( LogTemp , Error , TEXT( "gm - Next Receive Quest Tag: %s" ) , *nextquesttag );
	NextquestTag = nextquesttag;

	// Quest Receive -> MiniGame Active, Spawner Deactive
	OnNextMiniGameQuestTagReceived.Broadcast( NextquestTag );
	OnNextSpawnerQuestTagReceived.Broadcast( NextquestTag );
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
	case 3: index = 8; break; 
		default: break;
	}

	if(!IsToToNotInMapStart)
	{
		int32 SaveDataIndex = GI->FindLastToToSaveData(LevelIdx);

		// 저장된 데이터가 있다면	
		if(SaveDataIndex != -1)
		{
			int32 ThousandNum = SaveDataIndex / 1000;
			if(ThousandNum == 3) GI->ExecuteTutorial(EExplainType::ATTACK, -1, SaveDataIndex);
			else if(ThousandNum == 4) GI->ExecuteTutorial(EExplainType::SKILL, -1, SaveDataIndex);
			else if(ThousandNum == 9) GI->ExecuteTutorial(EExplainType::MAIN_STORY, -1, SaveDataIndex);
		}
		
		// 저장된 데이터가 없다면 처음부터 시작
		else GI->ExecuteTutorial(EExplainType::MAIN_STORY, index);
	}
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

void APlayerGameMode::ActivateInterationObject( bool onoff )
{
	for (TActorIterator<AStrangeObject> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		AStrangeObject* InteractionObject = *ActorItr;

		if (InteractionObject)
		{
			UE_LOG( LogTemp , Error , TEXT( "APlayerGameMode::ActivateInterationObject( bool onoff )" ) );
			//켜고 끄는 코드
			InteractionObject->ActiveMapIcon(onoff);
		}
	}
}

void APlayerGameMode::PlayOutroSequencer()
{
	UE_LOG( LogTemp , Log , TEXT( "APlayerGameMode::PlayOutroSequencer - Outro Sequencer Play" ) );

	// 레벨 내, 플레이어 보스 hidden
	for (TActorIterator<ABossMonster> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		ABossMonster* boss = *ActorItr;
		UE_LOG( LogTemp , Error , TEXT( "Boss hidden - false" ) );
		if(boss)
		{
			boss->SetHidden( true );
			UE_LOG( LogTemp , Error , TEXT( "Boss hidden - true" ) );
		}
	}
	if(Player)
	{
		Player->SetActorLocation( (FVector( -3380.0f ,5000.0f, -530.0f )));
		Player->PlayerDoSomeThing( true );
		FInputModeUIOnly InputModeUIOnly;
		Player->GetProjectDPlayerController()->SetInputMode( InputModeUIOnly );
	}
	

	if (!Lv3SequencePlayer && !bossComp && !playerComp) return;
	ASoundManager* SoundManager = ASoundManager::GetInstance( GetWorld() );

	if (Lv3SequencePlayer && OriginalViewTarget)
	{
		UE_LOG( LogTemp , Log , TEXT( "Success to create Level Sequence Player." ) );
		//bossComp->SetVisibility( true );
		bossComp->SetHiddenInGame( false );
		playerComp->SetHiddenInGame( false );

		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend( OriginalViewTarget , 1.0f );
		SoundManager->StopBGM();
		Lv3SequencePlayer->Play();
	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "Failed to create Level Sequence Player." ) );
	}

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {
			bossComp->DestroyComponent( true );
			Lv3SequencePlayer->Stop();  // 시퀀스 정지
			SAVE( Player , ESaveType::SAVE_MAIN , "PlayerMainSave" , "PlayerMainSave" , "Opening" , false );
			// UGameplayStatics::OpenLevel( this , TEXT("Opening") ); // <- Ending Credits이 끝나면 호출되게 EndingCreditsWidget의 AnimationFinished에서 호출 중

			// Ending Credits
			if(!EndingCreditsWidget && EndingCreditsFactory)
			{
				EndingCreditsWidget = CreateWidget<UEndingCreditsWidget>(GetWorld(), EndingCreditsFactory );
				EndingCreditsWidget->AddToViewport(static_cast<int32>(ViewPortPriority::Main));
			}
		} ,
		14.0f , // 지연 시간(초)
		false
	);

}


