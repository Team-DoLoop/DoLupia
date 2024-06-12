// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/StrangeObject.h"
#include <Components/BoxComponent.h>

#include "Characters/ProjectDCharacter.h"
#include "Data/WidgetData.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"

// Sets default values
AStrangeObject::AStrangeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComponent" ) );
	MeshComponent->SetupAttachment( BoxComponent );
}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();

	ChangeObjectOutline( 1 );
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

void AStrangeObject::ChangeObjectOutline(int32 depth)
{
	if (MeshComponent)
	{
		MeshComponent->SetRenderCustomDepth( true );
		MeshComponent->CustomDepthStencilValue = depth;
	}
}

