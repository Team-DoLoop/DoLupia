// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/MinigameQuestObject.h"

#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

AMinigameQuestObject::AMinigameQuestObject()
{
	static ConstructorHelpers::FClassFinder<AActor> minigame( TEXT( "/Game/UserInterface/MiniGame/BP_MiniGame2048.BP_MiniGame2048" ) );
	if (minigame.Succeeded())
	{
        MiniGameClass = minigame.Class;
	}
}

FString AMinigameQuestObject::InteractWith()
{
    if(!isAvailable)
    {
        auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
        int32 questid = gm->GetQuestID();

        if (questid == 2003)
        {
            SpawnMiniGame();
            isAvailable = true;
        }
    }
	return Super::InteractWith();
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
