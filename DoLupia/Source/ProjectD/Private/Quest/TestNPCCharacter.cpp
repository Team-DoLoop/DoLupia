// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/TestNPCCharacter.h"
#include <Components/BoxComponent.h>

#include "Characters/ProjectDCharacter.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"
#include "Quest/QuestGiver.h"

// Sets default values
ATestNPCCharacter::ATestNPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiverComp = CreateDefaultSubobject<UQuestGiver>( TEXT( "QuestGiverComp" ) );
    BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );
}

// Called when the game starts or when spawned
void ATestNPCCharacter::BeginPlay()
{
	Super::BeginPlay();

    NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
    NPCInteractGWidget->SetVisibility( ESlateVisibility::Hidden );
	
}

// Called every frame
void ATestNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestNPCCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

    if (OtherActor)
    {
        AProjectDCharacter* PlayerCharacter = Cast<AProjectDCharacter>( OtherActor );

        if (PlayerCharacter != nullptr)
        {
            NPCInteractGWidget->SetVisibility( ESlateVisibility::Visible );
        }
    }
}

void ATestNPCCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

    if (OtherActor)
    {
        AProjectDCharacter* PlayerCharacter = Cast<AProjectDCharacter>( OtherActor );

        if (PlayerCharacter != nullptr)
        {
            NPCInteractGWidget->SetVisibility( ESlateVisibility::Hidden );
        }
    }
}

// Called to bind functionality to input
void ATestNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Player -> NPC 인거 같음.
FString ATestNPCCharacter::InteractWith()
{
    // 먼저 QuestGiverComp가 유효한지 확인
    if (QuestGiverComp == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestGiverComp is null." ) );
        return FString( TEXT( "QuestGiverComp is null." ) );
    }

    // QuestGiverComp가 UQuestInteractionInterface를 구현하는지 확인
    if (!QuestGiverComp->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass() ))
    {
        return FString( TEXT( "QuestGiverComp does not implement UQuestInteractionInterface." ) );
    }

    // 인터페이스로 캐스팅 시도
    IQuestInteractionInterface* QuestInterface = Cast<IQuestInteractionInterface>( QuestGiverComp );

    if (QuestInterface == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to cast QuestGiverComp to IQuestInteractionInterface." ) );
        return FString( TEXT( "Failed to cast QuestGiverComp to IQuestInteractionInterface." ) );
    }

    // 인터페이스 메서드 호출 NPC -> QuestGiver
    return QuestInterface->InteractWith();
}

void ATestNPCCharacter::LookAt()
{

}
