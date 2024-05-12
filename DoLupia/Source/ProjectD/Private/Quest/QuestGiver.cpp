// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestGiver.h"

#include "Blueprint/UserWidget.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDGameMode.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/Struct_QuestSystem.h"
#include "UserInterface/Quest/WidgetQuestGiver.h"
#include "UserInterface/Quest/WidgetQuestRewards.h"
#include "Quest/Quest_Base.h"

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
    // 캐스팅이 유효한지 확인
    auto QuestComponent = Cast<UQuestLogComponent>( MyPlayerCharacter->FindComponentByClass( UQuestLogComponent::StaticClass() ) );
    if (QuestComponent == nullptr)
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestComponent not found or cast failed." ) );
        return FString( TEXT( "QuestComponent not found or cast failed." ) );
    }

    UE_LOG( LogTemp , Error , TEXT( "QuestData.RowName %s" ) , *QuestData.RowName.ToString() );

    bool ActiveQuest = QuestComponent->QueryActiveQuest( QuestData.RowName );

    if (!ActiveQuest)
    {
        //여기서 UWidgetQuestGiver 생성함. QuestID 넘김.
        UE_LOG( LogTemp , Error , TEXT( "!QuestComponent->QueryActiveQuest( QuestData.RowName )" ) );
        DisplayQuest();
        return GetOwner()->GetName();
    }
    else
    {
        if (QuestComponent == nullptr)
        {
            UE_LOG( LogTemp , Error , TEXT( "QuestComponent not found or cast failed." ) );
            return FString( TEXT( "QuestComponent not found or cast failed." ) );
        }

        AQuest_Base* CompleteValuePtr = QuestComponent->GetQuestActor( QuestData.RowName );
        if (CompleteValuePtr)
        {
            UE_LOG( LogTemp , Error , TEXT( "AQuest_Base* CompleteValuePtr = QuestComponent->GetQuestActor( QuestData.RowName )" ) );
            if (CompleteValuePtr->IsCompleted) 
            {
                UE_LOG( LogTemp , Error , TEXT( "DisplayRewards();" ) );
                //완료가 true이면
                DisplayRewards();
                return GetOwner()->GetName();
            }
            /*
                else 
            {
                UE_LOG( LogTemp , Error , TEXT( " DisplayQuest();" ) );
                //false이면
                DisplayQuest();
                return GetOwner()->GetName();
            }
            */
               
        }

        // 모든 조건을 처리한 후에도 값을 반환하지 않았으므로 기본값을 반환합니다.
        return FString( TEXT( "InteractWith function did not return a valid value." ) );
    }
}

void UQuestGiver::DisplayQuest()
{
    FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestData.RowName , TEXT( "Searching for row" ) , true );

    if (Row)
    {
		QuestWidget = CreateWidget<UWidgetQuestGiver>( GetWorld() , QuestGiverWidget );
        if (QuestWidget)
        {
	        QuestWidget->QuestDetails = *Row;
            QuestWidget->QuestID = QuestData.RowName;
			QuestWidget->AddToViewport(); // 위젯을 화면에 추가
        }
    }
}

void UQuestGiver::DisplayRewards()
{
    FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestData.RowName , TEXT( "Searching for row" ) , true );
    if (Row)
    {
        RewardsWidget = CreateWidget<UWidgetQuestRewards>( GetWorld() , QuestRewardsWidget );
        if (RewardsWidget)
        {
            RewardsWidget->QuestDetails = *Row;
            RewardsWidget->QuestID = QuestData.RowName;
            RewardsWidget->AddToViewport();
        }
    }   
}
