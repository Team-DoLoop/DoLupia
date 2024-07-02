// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/StrangeObject.h"
#include <Components/BoxComponent.h>

#include "Data/WidgetData.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"
#include "MapIconComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStrangeObject::AStrangeObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComponent" ) );
	MeshComponent->SetupAttachment( BoxComponent );

	//static ConstructorHelpers::FObjectFinder<UTexture2D> LocationIcon( TEXT( "/Game/Asset/Widget/MiniMap/search.search" ) );
	MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
	MapIcon->SetupAttachment( BoxComponent );
	// Set the player icon as texture
	//MapIcon->SetIconTexture( LocationIcon.Object );
	// The icon will rotate to represent the character's rotation
	MapIcon->SetIconRotates( false );
	MapIcon->SetIconVisible( false );

	gm = nullptr;
	
}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();
	NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	if (gm)
	{
		gm->OnNextMiniGameQuestTagReceived.AddDynamic( this , &AStrangeObject::OnNextQuestTagReceived );
	}
}

// Called every frame
void AStrangeObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStrangeObject::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!bVisibleInteractUI) return;

	if(NPCInteractWidget)
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

	if (!bVisibleInteractUI) return;

	if (NPCInteractGWidget)
	{
		NPCInteractGWidget->RemoveFromParent();
	}
}

FString AStrangeObject::InteractWith()
{
	bVisibleInteractUI = false;
	bCheckIcon = true;
	MeshComponent->SetRenderCustomDepth( false );

	if (gm)
	{
		gm->OnNextSpawnerQuestTagCompleted.RemoveDynamic( this , &AStrangeObject::OnNextQuestTagCompleted );
		gm->OnNextSpawnerQuestTagCompleted.AddDynamic( this, &AStrangeObject::OnNextQuestTagCompleted );
	}

	//QuestData 에 있는 Objective ID와 같아야함.
	return ObjectID;
}

void AStrangeObject::ActiveMapIcon(bool onoff)
{
	MapIcon->SetIconVisible( onoff );
}

void AStrangeObject::OnNextQuestTagReceived(FString NextQuestTag)
{
	if (TmpQuestTag.ToString() == NextQuestTag)
	{
		if (gm && gm->GetNxtQuestTag() != "")
		{
			if (TmpQuestTag == FName( gm->GetNxtQuestTag() ))
			{
				bVisibleInteractUI = true;
				ChangeObjectColor( 4 );
				ActiveMapIcon( true );
			}

		}
	}
}

void AStrangeObject::OnNextQuestTagCompleted()
{
	bCheckIcon = false;
	bVisibleInteractUI = false;
	MeshComponent->SetRenderCustomDepth( false );
	ActiveMapIcon( false );
}

void AStrangeObject::ChangeObjectColor(int32 depth)
{
	if (!bVisibleInteractUI) return;
	MeshComponent->SetRenderCustomDepth( true );
	MeshComponent->SetCustomDepthStencilValue( depth );
	MapIcon->SetVisibility( true );
}

