// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest/QuestLogComponent.h"
#include "Quest/Quest_Base.h"  // AQuest_Base 사용
#include "UserInterface/Quest/QuestTracker.h"


// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<UQuestTracker> WidgetClassFinder( TEXT( "/Game/QuestSystem/WBP_QuestTracker.WBP_QuestTracker_C" ) );
    if (WidgetClassFinder.Succeeded())
    {
        QuestTracker_Widget = WidgetClassFinder.Class;
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to load widget class" ) );
    }
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
            
            auto* QuestActor = GetQuestActor( QuestID );
            if (QuestActor != nullptr)
            {
                // Set IsTurnedIn to true and broadcast the event
                QuestActor->IsTurnedIn = true;
                //QuestTracker로 받음.
                QuestCompleted.Broadcast( QuestActor );
            }
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

bool UQuestLogComponent::QueryCompleteQuests(FName QuestID)
{
    //현재 퀘스트에 특정 퀘스트 아이디가 있는지에 대한 bool 값
    bool QuestExist = CompletedQuests.Contains( QuestID );
    if (QuestExist) {
        UE_LOG( LogTemp , Error , TEXT( "True CompletedQuests(FName %s)" ) , *QuestID.ToString() );
    }
    else {
        UE_LOG( LogTemp , Error , TEXT( "False CompletedQuestst(FName %s)" ) , *QuestID.ToString() );
    }
    return QuestExist;
}

bool UQuestLogComponent::QueryCompleteQuestsTurnedIn(FName QuestID )
{
	if(IsValid(GetQuestActor(QuestID)))
	{
        return GetQuestActor(QuestID)->IsTurnedIn;
	}else
	{
        return true;
	}
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

void UQuestLogComponent::TrackQuest( AQuest_Base* QuestActor )
{
    if (IsValid( Tracker ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Tracker is valid." ) );

        // Tracker가 이미 존재하면 Update 호출
        Tracker->Remove();
        Tracker = nullptr;
        Tracker = CreateWidget<UQuestTracker>( GetWorld() , QuestTracker_Widget );

        if (IsValid( Tracker ))
        {
            Tracker->QuestActor = QuestActor;
            Tracker->AddToViewport( -1 );

            // 초기화 호출
            Tracker->WidgetUpdate();
        }
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "Tracker is not valid." ) );

        // Tracker가 존재하지 않으면 새로 생성
        Tracker = CreateWidget<UQuestTracker>( GetWorld() , QuestTracker_Widget );

        if (IsValid( Tracker ))
        {
            Tracker->QuestActor = QuestActor;
            Tracker->AddToViewport( -1 );

            // 초기화 호출
            Tracker->WidgetUpdate();
        }
    }
}

