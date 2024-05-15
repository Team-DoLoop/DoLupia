// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest/QuestLogComponent.h"
#include "Quest/Quest_Base.h"  // AQuest_Base 사용


// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UQuestLogComponent::AddNewQuest(FName QuestID)
{
    if (QuestID.IsNone())
    {
        UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ QuestLogComponent" ) );
        return;
    }

    // 생성자에 QuestID를 전달하여 AQuest_Base를 생성합니다.
    AQuest_Base* SpawneQuest = GetWorld()->SpawnActor<AQuest_Base>( AQuest_Base::StaticClass() );

	if (!SpawneQuest)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to spawn AQuest_Base" ) );
        return;
    }
    else
    {
        //QuestID quest_Base에 보내기
        OnQuestDataLoaded.Broadcast( QuestID );
        CurrentActiveQuests.AddUnique( QuestID );
        SpawneQuest->QuestID = QuestID;
        UE_LOG( LogTemp , Error , TEXT( "void UQuestLogComponent::AddNewQuest(FName QuestID): %s" ) , *QuestID.ToString() );

    }

	//현재 퀘스트에 스폰한 퀘스트를 추가
	CurrentQuest.Add( SpawneQuest );
}

void UQuestLogComponent::CompleteQuest( FName QuestID )
{
    CompletedQuests.AddUnique( QuestID );
    CurrentActiveQuests.Remove( QuestID );

    // CurrentQuest 목록에서도 해당 퀘스트 제거
    for (int32 i = 0; i < CurrentQuest.Num(); ++i)
    {
        if (CurrentQuest[i]->QuestID == QuestID)
        {
            CurrentQuest.RemoveAt( i );
            QuestCompleted.Broadcast(GetQuestActor(QuestID));

            break;
        }
    }
}

void UQuestLogComponent::TurnInQuest( FName QuestID )
{
    AQuest_Base* Quest = GetQuestActor( QuestID );
    if (Quest)
    {
        CompleteQuest( QuestID );
        // Quest 객체의 멤버에 접근하는 작업 추가...
        Quest->CurrentStageDetails;
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to find quest with ID %s" ) , *QuestID.ToString() );
    }

}

bool UQuestLogComponent::QueryActiveQuest(FName QuestID)
{
	//현재 퀘스트에 특정 퀘스트 아이디가 있는지에 대한 bool 값
	bool QuestExist = CurrentActiveQuests.Contains(QuestID);
    if (QuestExist) {
        UE_LOG( LogTemp , Error , TEXT( "True QueryActiveQuest(FName %s)") , *QuestID.ToString() );
    }
    else {
        UE_LOG( LogTemp , Error , TEXT( "False QueryActiveQuest(FName %s)" ) , *QuestID.ToString() );
    }
	return QuestExist;
}

AQuest_Base* UQuestLogComponent::GetQuestActor( FName QuestID )
{
    for (const auto& Quest : CurrentQuest)
    {
        UE_LOG( LogTemp , Error , TEXT( "void UQuestLogComponent::AddNewQuest(FName QuestID): %s" ) , *Quest->QuestID.ToString() );
        if (Quest->QuestID == QuestID)
        {
            UE_LOG( LogTemp , Error , TEXT( "Quest->QuestID == QuestID" ));
            return Quest;
        }
    }
    // 퀘스트를 찾지 못한 경우 nullptr를 반환합니다.
    UE_LOG( LogTemp , Error , TEXT( "Quest->QuestID == nullptr" ) );
    return nullptr;
}

