// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/PlayerGameMode.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/ProjectDCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "Library/AIConnectionLibrary.h"
#include "UserInterface/NPC/NPCConvWidget.h"

APlayerGameMode::APlayerGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectDPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass( TEXT( "/Game/TopDown/Blueprints/BP_TopDownCharacter" ) );
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

}

void APlayerGameMode::StartPlay()
{
	Super::StartPlay();
	
	// Get or create the AIConnectionLibrary instance
	AIlib = UAIConnectionLibrary::GetInstance( this );

	if (AIlib) {
		UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::StartPlay - AIlib Success" ) )
	}
	else {
		UE_LOG( LogTemp , Warning , TEXT( "APlayerGameMode::StartPlay - AIlib Failed" ) )
	}
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

void APlayerGameMode::ReceiveNPCConv( FString Response )
{
	NPCConversation = Response;
	UE_LOG( LogTemp , Warning , TEXT( "NPCConversation : [%s]" ) , *NPCConversation )
	
	
	if (NPCConvUI)
    {
        NPCConvUI->SetupNPCConv( Response );
    }
	
}
