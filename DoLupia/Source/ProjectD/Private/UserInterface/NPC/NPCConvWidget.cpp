// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/NPC/NPCConvWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Gamemode/PlayerGameMode.h"
#include <Kismet/GameplayStatics.h>

void UNPCConvWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNPCConvWidget::SetupNPCConv( FString conv )
{
	txt_NPCConv->SetText( FText::FromString( conv ) );
}
