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



}

void APlayerGameMode::StartPlay()
{
	Super::StartPlay();

	// Get or create the AIConnectionLibrary instance
	AIlib = UAIConnectionLibrary::GetInstance( this );

	AITestUI = CreateWidget<UAITestWidget>( GetWorld() , AITestUIFactory );
	if (AITestUI)
	{
		AITestUI->AddToViewport( 999 );
		
		// Set input mode to UI only and set the widget to focus
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			//FInputModeUIOnly InputMode;
			FInputModeGameOnly InputMode;

			//InputMode.SetWidgetToFocus( AITestUI->TakeWidget() );
			//PlayerController->SetInputMode( InputMode );
			//PlayerController->bShowMouseCursor = true;

			InputMode.SetConsumeCaptureMouseDown( true );
			PlayerController->SetInputMode( FInputModeUIOnly() );

		}

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
}
