// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/MinigameQuestObject.h"

#include "MapIconComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

AMinigameQuestObject::AMinigameQuestObject()
{
	static ConstructorHelpers::FClassFinder<AActor> minigame( TEXT( "/Game/UserInterface/MiniGame/BP_MiniGame2048.BP_MiniGame2048" ) );
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

    if(gm)
    {
        gm->OnNextMiniGameQuestTagReceived.AddDynamic( this , &AMinigameQuestObject::OnNextMiniGameQuestTagReceived );
    }
    MapIcon->SetVisibility( false );
}

FString AMinigameQuestObject::InteractWith()
{
    FString test = "";
    if(!isAvailable)
    {
        int32 questid = gm->GetQuestID();

        if (questid == 2002)
        {
            SpawnMiniGame();
            isAvailable = true;
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
