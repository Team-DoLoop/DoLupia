﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/TestItem.h"
#include "Components/SphereComponent.h"
#include <Characters/ProjectDCharacter.h>
#include "Quest/QuestInventoryComponent.h"

ATestItem::ATestItem()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MyCollisionSphere = CreateDefaultSubobject<USphereComponent>( TEXT( "My Collision Sphere" ) );
}

void ATestItem::NotifyActorBeginOverlap( AActor* OtherActor )
{
    if (OtherActor)
    {
        AProjectDCharacter* PlayerCharacter = Cast<AProjectDCharacter>( OtherActor );

        if (PlayerCharacter != nullptr)
        {
            UQuestInventoryComponent* QuestInventoryComp = PlayerCharacter->FindComponentByClass<UQuestInventoryComponent>();
            if (QuestInventoryComp != nullptr)
            {
                // FName을 생성하여 전달하고, 필요에 따라 아이템의 수량을 지정할 수 있습니다.
                //FName ItemName = FName( TEXT( "testitem" ) );
                //int32 Quantity = 1;
                FObjectiveID_Value BroadCastMap;
                BroadCastMap.ObjectiveID_Value.Add( "testitem" , 1 );
                QuestInventoryComp->AddToInventory( BroadCastMap );

                // 부딪힌 아이템을 삭제합니다.
                Destroy();
            }
        }
    }
}


// Called when the game starts or when spawned
void ATestItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

