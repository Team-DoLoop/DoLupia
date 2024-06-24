// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/MinigameQuestObject.h"

#include "MapIconComponent.h"
#include "Pooling/SoundManager.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGame/Grid2048.h"

AMinigameQuestObject::AMinigameQuestObject()
{
	static ConstructorHelpers::FClassFinder<AActor> minigame( TEXT( "/Game/UserInterface/MiniGame/BP_MiniGame2048" ) );
	if (minigame.Succeeded())
	{
        MiniGameClass = minigame.Class;
	}
    gm = nullptr;

}

void AMinigameQuestObject::BeginPlay()
{
	Super::BeginPlay();

    gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
    Player = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
    
    if(gm)
    {
        gm->OnNextMiniGameQuestTagReceived.AddDynamic( this , &AMinigameQuestObject::OnNextMiniGameQuestTagReceived );
    }
    MapIcon->SetVisibility( false );

}

FString AMinigameQuestObject::InteractWith()
{
    Super::InteractWith();

    if(!isAvailable)
    {
        int32 questid = gm->GetQuestID();

        if (questid == 2002)
        {
            SpawnMiniGame();
            isAvailable = true;

            //미니게임 비지엠 시작
            if (ASoundManager* SoundManager = ASoundManager::GetInstance( GetWorld() ))
            {
                if (BGMSoundWave) SoundManager->PlayBGM( BGMSoundWave , 0.2f );
            }

            return ObjectID;
        }
    }

    return ObjectID;
}

/*
FString AMinigameQuestObject::GetOwnQuestID() const
{
    return OwnQuestID;
}
*/

void AMinigameQuestObject::ChangeMinigameColor(int32 depth)
{
    if (!bVisibleInteractUI) return;
    MeshComponent->SetRenderCustomDepth( true );
    MeshComponent->SetCustomDepthStencilValue( depth );
    MapIcon->SetVisibility( true );
}

void AMinigameQuestObject::OnNextMiniGameQuestTagReceived(FString NextQuestTag)
{
    if (OwnQuestTag.ToString() == NextQuestTag)
    {
        UpdateMiniGameStatus();
    }
}

void AMinigameQuestObject::OnNextSpawnerQuestTagCompleted()
{
    //MeshComponent->SetRenderCustomDepth( false );
    // ICON 삭제
    MapIcon->DestroyComponent( true );
    bCheckIcon = false;
}

void AMinigameQuestObject::SpawnMiniGame()
{
    if (MiniGameClass != nullptr)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        // 스폰 위치와 회전 설정
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();

        // 액터 스폰
        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>( MiniGameClass , SpawnLocation , SpawnRotation , SpawnParams );
        if (!SpawnedActor) return;

        Ownminigame = Cast<AGrid2048>( SpawnedActor );

        if (Ownminigame)
        {
            Ownminigame->OnMiniGameCompleted.AddDynamic( this , &AMinigameQuestObject::OnNextSpawnerQuestTagCompleted );
        }

        Player->PlayerDoSomeThing(true);
    }
}

void AMinigameQuestObject::UpdateMiniGameStatus()
{
    if (gm && gm->GetNxtQuestTag() != "")
    {
        if (OwnQuestTag == FName( gm->GetNxtQuestTag() ))
        {
            // 태그 값이 일치하면 상태 변경 로직 추가
            UE_LOG( LogTemp , Log , TEXT( "MiniGame with tag %s received matching Quest ID: %s" ) , *OwnQuestTag.ToString() , *CurrentQuestTag );

            ChangeMinigameColor( 4 );
        }
    	
    }
}
