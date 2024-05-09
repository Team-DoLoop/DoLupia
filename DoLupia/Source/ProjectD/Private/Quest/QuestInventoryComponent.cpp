// Fill out your copyright notice in the Description page of Project Settings.


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

void UQuestInventoryComponent::AddToInventory( FName Item , int32 Quantity )
{
	FString ItemString = Item.ToString(); // FName을 FString으로 변환

	int32* ExistingQuantity = Content.Find( ItemString ); // 해당 아이템의 수량을 찾음

	if (ExistingQuantity) // 만약 해당 아이템이 이미 맵에 존재한다면
	{
		auto PlusQuantity = (*ExistingQuantity) + Quantity; // 수량을 더해줌
		Content.Add( ItemString , PlusQuantity); // 새로운 아이템과 수량을 추가함
	}

	//플레이어에 있는 방송을 가져와서 아이템 이름을 보냄!!
	ProjectDCharacter->OnObjectiveIDCalled.Broadcast(ItemString, Quantity );

}

