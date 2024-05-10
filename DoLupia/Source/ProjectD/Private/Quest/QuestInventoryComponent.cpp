﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestInventoryComponent.h"
#include <Characters/ProjectDCharacter.h>

// Sets default values for this component's properties
UQuestInventoryComponent::UQuestInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid( PlayerController ))
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerController is not valid." ) );
		return;
	}

	ACharacter* PlayerCharacter = Cast<ACharacter>( PlayerController->GetPawn() );
	if (!IsValid( PlayerCharacter ))
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerCharacter is not valid." ) );
		return;
	}

	// 가져온 플레이어 캐릭터가 ProjectDCharacter 클래스의 인스턴스인지 확인
	ProjectDCharacter = Cast<AProjectDCharacter>( PlayerCharacter );
	if (!IsValid( ProjectDCharacter ))
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / ProjectDCharacter is not valid." ) );
		return;
	}
	
}


// Called every frame
void UQuestInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestInventoryComponent::AddToInventory( FObjectiveID_Value BroadCastMap )
{
	for (const auto& KeyValue : BroadCastMap) {
		FString ItemString = KeyValue.Key().ToString(); // FName을 FString으로 변환

		int32* ExistingQuantity = Content.Find( ItemString ); // 해당 아이템의 수량을 찾음

		if (ExistingQuantity) // 만약 해당 아이템이 이미 맵에 존재한다면
		{
			UE_LOG( LogTemp , Warning , TEXT( "AddToInventory FName: %s, Inventory Count: %d" ) , *KeyValue.Key().ToString() , KeyValue.Value() );
			auto PlusQuantity = (*ExistingQuantity) + KeyValue.Value(); // 수량을 더해줌
			Content.Add( ItemString , PlusQuantity ); // 새로운 아이템과 수량을 추가함
		}
		else
		{
			//처음 얻을때
			UE_LOG( LogTemp , Warning , TEXT( "First AddToInventory FName: %s, Inventory Count: %d" ) , *KeyValue.Key().ToString() , KeyValue.Value() );
			Content.Add( ItemString , KeyValue.Value() );
		}
		//플레이어에 있는 방송을 가져와서 아이템 이름을 보냄!!
		FObjectiveID_Value QIBroadCastMap;
		QIBroadCastMap.ObjectiveID_Value.Add( ItemString , KeyValue.Value() );
		ProjectDCharacter->OnObjectiveIDCalled.Broadcast( QIBroadCastMap );
	}
}

int32 UQuestInventoryComponent::QueryInventory( FName Item )
{
	// Content 맵이 유효한지 확인
	if (Content.Num() <= 0)
	{
		UE_LOG( LogTemp , Warning , TEXT( "QueryInventory Content map is empty or null." ) );
		return 0; // 이 경우 0 또는 다른 기본값을 반환할 수 있습니다.
	}
	FString ItemString = Item.ToString();
	return *Content.Find( ItemString );
}