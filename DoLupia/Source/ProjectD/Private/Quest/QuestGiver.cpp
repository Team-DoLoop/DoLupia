﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestGiver.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDGameMode.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/Struct_QuestSystem.h"

// Sets default values for this component's properties
UQuestGiver::UQuestGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 데이터 테이블 로드
    UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/QuestData.QuestData" ) );

	if (DataTable)
	{
		// 데이터 테이블이 성공적으로 로드된 경우 작업 수행
		QuestData.DataTable = DataTable;  // 데이터 테이블 설정
		//QuestData.RowName = FName("DefaultRow");  // 행 이름 설정
	}
	else
	{
		// 로드 실패 시 처리
		UE_LOG(LogTemp, Error, TEXT("Data table not found!"));
	}
}


// Called when the game starts
void UQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
    UWorld* World = GetWorld();
    if (!World) return;

    // 플레이어 캐릭터를 가져옵니다.
    MyPlayerCharacter = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( World , 0 ) );

    MyGameMode = Cast<AProjectDGameMode>( UGameplayStatics::GetGameMode( World ) );
}


// Called every frame
void UQuestGiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UQuestGiver::InteractWith()
{
    if (MyPlayerCharacter == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "MyPlayerCharacter is null." ) );
        return FString( TEXT( "Invalid MyPlayerCharacter" ) );
    }

    // 캐스팅이 유효한지 확인
    auto QuestComponent = Cast<UQuestLogComponent>( MyPlayerCharacter->FindComponentByClass( UQuestLogComponent::StaticClass() ) );
    if (QuestComponent == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestComponent not found or cast failed." ) );
        return FString( TEXT( "QuestComponent not found or cast failed." ) );
    }

    if (!QuestComponent->QueryActiveQuest( QuestData.RowName ))
    {
        DisplayQuest();
        return GetOwner()->GetName();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage( -1 , 5.0f , FColor::Red , TEXT( "Already on Quest" ) );
        return GetOwner()->GetName();
    }
}

void UQuestGiver::DisplayQuest()
{
    if (QuestData.DataTable == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestData.DataTable is null." ) );
        return;
    }

    FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestData.RowName , TEXT( "Searching for row" ) , true );

    if (Row)
    {
        GEngine->AddOnScreenDebugMessage( -1 , 5.0f , FColor::Red , Row->QuestName );  // 5초간 빨간색으로 표시
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "Quest row not found." ) );
    }
}