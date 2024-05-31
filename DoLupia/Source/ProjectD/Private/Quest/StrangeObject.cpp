// Fill out your copyright notice in the Description page of Project Settings.


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

	// 위젯 컴포넌트의 부모 설정 (루트 컴포넌트에 붙이거나 다른 컴포넌트에 붙일 수 있습니다)
	WidgetComponent->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void AStrangeObject::BeginPlay()
{
	Super::BeginPlay();
	NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
	WidgetComponent->SetWidget( NPCInteractGWidget );
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
		}
	}
}

FString AStrangeObject::InteractWith()
{
	//QuestData 에 있는 Objective ID와 같아야함.
	return ObjectID;
}

