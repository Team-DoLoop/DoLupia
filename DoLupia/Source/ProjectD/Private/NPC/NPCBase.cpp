// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	if (gm)
	{
		UE_LOG( LogTemp , Warning , TEXT( "gm - Load Success" ) );
	}
	else {
		UE_LOG( LogTemp , Warning , TEXT( "gm - Load Failed" ) );
	}

	//gm->InitializeNPCConvWidget();
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::NotifyActorBeginOverlap( AActor* OtherActor )
{
	AProjectDCharacter* player = Cast<AProjectDCharacter>( OtherActor );

	UE_LOG( LogTemp , Warning , TEXT( "NPC Test" ) );

	

	UE_LOG( LogTemp , Warning , TEXT( "NPCConversation : [%s]" ) , *NPCConversation )

	if (player)
	{
		AIlib = gm->GetAIConnectionLibrary();
		UE_LOG( LogTemp , Warning , TEXT( "NPC - Overlap Player" ) );

		// 현재 활성 레벨을 world context object로 사용하여 AIlib 함수를 호출합니다.
		if (AIlib)
		{
			BeginChat();
		}
		else {
			UE_LOG( LogTemp , Warning , TEXT( "AIlib - Load failed" ) );
		}

	}
}

void ANPCBase::BeginChat()
{
	if (AIlib) {
		AIlib->OnWebApiResponseReceived.AddDynamic( this , &ANPCBase::CallNPCMessageDelegate );
		UE_LOG( LogTemp , Warning , TEXT( "AIlib - First Load Sucess" ) );

		FString testStr = "이게 무슨 일이죠?";
		AIlib->SendNPCConversationToServer( testStr );

		
	}
	else {
		UE_LOG( LogTemp , Warning , TEXT( "AIlib - First Load failed" ) );
	}
}

void ANPCBase::CallNPCMessageDelegate( FString Message )
{
	NPCConversation = Message;
	UE_LOG( LogTemp , Warning , TEXT( "Message : [%s]" ) , *Message )

	gm->ReceiveNPCMsg( NPCConversation );

}


