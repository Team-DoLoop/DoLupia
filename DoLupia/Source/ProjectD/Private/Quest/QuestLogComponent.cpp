// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest/QuestLogComponent.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Quest/Quest_Base.h"  // AQuest_Base 사용
#include "UserInterface/Quest/QuestTracker.h"

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    static ConstructorHelpers::FClassFinder<UQuestTracker> WidgetClassFinder( TEXT( "/Game/UserInterface/Quest/WBP_QuestTracker.WBP_QuestTracker_C" ) );
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

    // FFileHelper 클래스를 이용하여 로그 파일 생성
    FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
    FFileHelper::SaveStringToFile( L"UQuestLogComponent::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
        &IFileManager::Get() , ELogVerbosity::Log );

	// ...
    
    GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if(GI)
    {
	   if(!GI->GetCompletedQuest().IsEmpty())
	   {
           CompletedQuests = GI->GetCompletedQuest();
           UE_LOG( LogTemp , Error , TEXT( "CompletedQuests = GI->GetCompletedQuest();" ) );
	   }
    }
    else
    {
        FFileHelper::SaveStringToFile( L"UQuestInventoryComponent::BeginPlay -> GI nullptr" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
            &IFileManager::Get() , ELogVerbosity::Log );
    }

    FFileHelper::SaveStringToFile( L"UQuestInventoryComponent::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
        &IFileManager::Get() , ELogVerbosity::Log );
    
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
       //spawneQuest->QuestID = QuestID;
        UE_LOG( LogTemp , Error , TEXT( "void UQuestLogComponent::AddNewQuest(FName QuestID): %s" ) , *QuestID.ToString() );

        //현재 퀘스트에 스폰한 퀘스트를 추가
        CurrentQuest.Add( SpawneQuest );
        UE_LOG( LogTemp , Error , TEXT( "CurrentQuest.Num(): %d" ) , CurrentQuest.Num() );
        //QuestID quest_Base에 보내기
        //OnQuestDataLoaded.Broadcast( QuestID );

        CurrentActiveQuests.AddUnique( QuestID );

        //QuestBase에서 보내기 GetQuestDetails
        UpdateCurrentActiveQuest.Broadcast();
    }

    //로케이션 마커 활성화
    auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
    if (QuestID == "0001" || QuestID == "1001" || QuestID == "2001")
    {
        gm->ActivateMarkers( 1 );
    }
    else if (QuestID == "1002") 
    {
        gm->ActivateMarkers( 2 );
        gm->ActivateMarkers( 3 );
    }
    else if (QuestID == "2004")
    {
        gm->ActivateMarkers( 4 );
    }
    if(QuestID == "0002")
    {
        //gm->ActivateInterationObject(true);
    }

}

void UQuestLogComponent::CompleteQuest( FName QuestID )
{
    /*망토 바꾸기
    auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
    auto AIlib = gm->GetAIConnectionLibrary();
    gm->ApplyAITxtP();
    */

    // 플레이어 대화 상태 갱신
    //auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
    //player->EnableDialogue();

	UE_LOG( LogTemp , Error , TEXT( "CompleteQuest( FName QuestID )" ) );
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

    RemoveTracker();

    auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
    //포털 열기
    if (QuestID == "3001" || QuestID == "1003") {
        gm->ActiveLvTrigger();
    }else if(QuestID == "1002")
    {
        gm->ActivateBarrierObject(false);
    }

    // 튜토리얼 스킬 열기
    if(QuestID == "0002")
    {
        Player->GetAttackComp()->SetSkillUseState(true, QUEST);

        // 각 색깔 열리게
        Player->GetAttackComp()->SetColorUseState(EUseColor::RED, true);
        Player->GetAttackComp()->SetColorUseState(EUseColor::YELLOW, true);
        Player->GetAttackComp()->SetColorUseState(EUseColor::BLUE, true);
    }

    else if(QuestID == "0004")
    {
        Player->GetAttackComp()->SetSkillUseState(false, QUEST);

        // 각 색깔 잠구기
        Player->GetAttackComp()->SetColorUseState(EUseColor::RED, false);
        Player->GetAttackComp()->SetColorUseState(EUseColor::YELLOW, false);
        Player->GetAttackComp()->SetColorUseState(EUseColor::BLUE, false);
    }
    

    //UE_LOG( LogTemp , Error , TEXT( "CompleteQuest( QuestID : %s )" ), *QuestID.ToString() );
    //gm->SetNxtQuestTag( QuestID.ToString() );

    // 튜토리얼 퀘스트 완료 관련
    if(GI)
    {
        if(auto _QuestData = GI->GetQuestData(QuestID))
        {
            if(_QuestData->AutoStory.IsAutoStory)
            {
                GI->ExecuteTutorial(_QuestData->AutoStory.QuestStoryType, -1, _QuestData->AutoStory.QuestStoryID);
            }

        }
        InitCompletedQuests(QuestID);
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

void UQuestLogComponent::AddToTracker()
{
    /*if(GetQuestActor(QuestID))
    {
        UE_LOG( LogTemp , Error , TEXT( "TrackQuest( Quest )" ) );
        TrackQuest( GetQuestActor( QuestID ) );
    }else
    {
        UE_LOG( LogTemp , Error , TEXT( "CurrentQuest.IsEmpty()" ) );
    }*/

    if (CurrentQuest.IsValidIndex(0))
    {
        for (const auto& Quest : CurrentQuest)
        {
            UE_LOG( LogTemp , Error , TEXT( "TrackQuest( Quest )" ) );
            TrackQuest( Quest );
        }
    }
    else
    {
        UE_LOG( LogTemp , Error , TEXT( "CurrentQuest.IsEmpty()" ) );
    }
}

void UQuestLogComponent::RemoveTracker()
{
    if(Tracker)
    {
        Tracker->Remove();
        Tracker = nullptr;
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
    if (IsValid( GetQuestActor( QuestID ) ))
    {
        GetQuestActor( QuestID )->IsTurnedIn = false;
    }
    else {
        //GetQuestActor( QuestID )->IsTurnedIn = true;
    }

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
            UE_LOG( LogTemp , Error , TEXT( "GetQuestActor:Quest->QuestID == QuestID" ));
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

void UQuestLogComponent::InitCompletedQuests( FName InitQuestID )
{
    if (GI)
    {
        GI->SetCompletedQuest( InitQuestID );
        UE_LOG( LogTemp , Error , TEXT( "GI->SetCompletedQuest( InitQuestID );" ) );
    }
   
}

