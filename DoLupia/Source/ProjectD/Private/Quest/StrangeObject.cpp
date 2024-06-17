// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/StrangeObject.h"
#include <Components/BoxComponent.h>

#include "Characters/ProjectDCharacter.h"
#include "Data/WidgetData.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"
#include "MapIconComponent.h"

// Sets default values
AStrangeObject::AStrangeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComponent" ) );
	MeshComponent->SetupAttachment( BoxComponent );

	/*static ConstructorHelpers::FObjectFinder<UTexture2D> LocationIcon( TEXT( "/Game/Asset/Widget/MiniMap/speech-bubble.speech-bubble" ) );
	MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
	MapIcon->SetupAttachment( GetRootComponent() );
	// Set the player icon as texture
	MapIcon->SetIconTexture( LocationIcon.Object );
	// The icon will rotate to represent the character's rotation
	MapIcon->SetIconRotates( false );
	//MapIcon->SetIconVisible( false );*/
	
}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStrangeObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStrangeObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(NPCInteractWidget)
	{
		NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
	NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}else
	{
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {
			NPCInteractGWidget->RemoveFromParent();
		} ,
		2.0f , // 지연 시간(초)
		false
		);

}

void AStrangeObject::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (NPCInteractGWidget)
	{
		NPCInteractGWidget->RemoveFromParent();
	}
}

FString AStrangeObject::InteractWith()
{
	//QuestData 에 있는 Objective ID와 같아야함.
	return ObjectID;
}

