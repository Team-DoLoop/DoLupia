// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/NPC/NPCConvWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Gamemode/PlayerGameMode.h"
#include <Kismet/GameplayStatics.h>

void UNPCConvWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	btn_startConversation->OnClicked.AddDynamic( this , &UNPCConvWidget::StartConversation );

}

void UNPCConvWidget::SetupNPCConv( FString conv )
{
	txt_NPCConv->SetText( FText::FromString( conv ) );
}

void UNPCConvWidget::StartConversation()
{
	SetupNPCConv( gm->NPCConversation );
}
