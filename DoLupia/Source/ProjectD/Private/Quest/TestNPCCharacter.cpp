// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/TestNPCCharacter.h"

#include "Quest/QuestGiver.h"

// Sets default values
ATestNPCCharacter::ATestNPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiverComp = CreateDefaultSubobject<UQuestGiver>( TEXT( "QuestGiverComp" ) );
}

// Called when the game starts or when spawned
void ATestNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
        UE_LOG( LogTemp , Error , TEXT( "QuestGiverComp does not implement UQuestInteractionInterface." ) );
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
	IQuestInteractionInterface::LookAt();

}
