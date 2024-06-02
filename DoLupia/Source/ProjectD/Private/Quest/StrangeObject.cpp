﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/StrangeObject.h"
#include <Components/BoxComponent.h>

#include "Characters/ProjectDCharacter.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"

// Sets default values
AStrangeObject::AStrangeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>( TEXT( "InteractWidget" ) );

	WidgetComponent->SetupAttachment( BoxComponent);
}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();
	NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
	WidgetComponent->SetWidget( NPCInteractGWidget );
	WidgetComponent->SetCastShadow( false );
	WidgetComponent->SetVisibility( false );
}

// Called every frame
void AStrangeObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStrangeObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor)
	{
		AProjectDCharacter* PlayerCharacter = Cast<AProjectDCharacter>( OtherActor );

		if (PlayerCharacter != nullptr)
		{
			WidgetComponent->SetVisibility( true );
			UE_LOG(LogTemp, Error, TEXT("WidgetComponent->SetVisibility( true );"))
		}
	} 
}

void AStrangeObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor)
	{
		AProjectDCharacter* PlayerCharacter = Cast<AProjectDCharacter>( OtherActor );

		if (PlayerCharacter != nullptr)
		{
			WidgetComponent->SetVisibility( false );
			UE_LOG( LogTemp , Error , TEXT( "WidgetComponent->SetVisibility( false );" ) )
		}
	}
}

FString AStrangeObject::InteractWith()
{
	//QuestData 에 있는 Objective ID와 같아야함.
	return ObjectID;
}

