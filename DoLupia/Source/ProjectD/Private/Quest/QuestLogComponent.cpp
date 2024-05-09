// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest/QuestLogComponent.h"
#include "Quest/Quest_Base.h"  // AQuest_Base 사용


// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//WidgetQuestGiver 에서 QuestId 받음
void UQuestLogComponent::AddNewQuest( FName QuestID )
{
    CurrentActiveQuests.AddUnique( QuestID );

    OnQuestDataLoaded.Broadcast( QuestID );

    if (QuestID.IsNone())
    {
        UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ QuestLogComponent" ) );
        return;
    }

    UE_LOG( LogTemp , Error , TEXT( "QuestID: %s" ) , *QuestID.ToString() );

    // 생성자에 QuestID를 전달하여 AQuest_Base를 생성합니다.
    AQuest_Base* SpawneQuest = GetWorld()->SpawnActor<AQuest_Base>( AQuest_Base::StaticClass() );
    if (!SpawneQuest)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to spawn AQuest_Base" ) );
        return;
    }
    else
    {
        SpawneQuest->QuestID = QuestID;
        UE_LOG( LogTemp , Error , TEXT( "QuestID: %s SpawneQuest->QuestID") , *QuestID.ToString() );
    }

    // 현재 퀘스트에 스폰한 퀘스트를 추가합니다.
    CurrentQuest.Add( SpawneQuest );
}


bool UQuestLogComponent::QueryActiveQuest(FName QuestID)
{
	//현재 퀘스트에 특정 퀘스트 아이디가 있는지에 대한 bool 값
	bool QuestExist = CurrentActiveQuests.Contains(QuestID);
	return QuestExist;
}

