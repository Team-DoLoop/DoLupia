// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Quest_Base.h"
#include "Quest/QuestLogComponent.h"
#include <Characters/ProjectDCharacter.h>
#include "Data/WidgetData.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Components/InventoryComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/Quest/WidgetQuestNotification.h"

// Sets default values
AQuest_Base::AQuest_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/Data/QuestDataTable.QuestDataTable" ) );

	if (DataTable)
	{
		// 데이터 테이블이 성공적으로 로드된 경우 작업 수행
		QuestData.DataTable = DataTable;  // 데이터 테이블 설정
	}
	else
	{
		// 로드 실패 시 처리
		UE_LOG( LogTemp , Error , TEXT( "Data table not found!" ) );
	}

	//_C!!!!!
	static ConstructorHelpers::FClassFinder<UWidgetQuestNotification> WidgetClassFinder( TEXT( "/Game/UserInterface/Quest/WBP_WidgetQuestNotification.WBP_WidgetQuestNotification_C" ) );
	if (WidgetClassFinder.Succeeded())
	{
		Notification_Widget = WidgetClassFinder.Class;
	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "Failed to load widget class" ) );
	}

}

// Called when the game starts or when spawned
void AQuest_Base::BeginPlay()
{
	Super::BeginPlay();

	//겜모에 QuestID 가져오기
	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	// 2단계: FString을 FName으로 변환
	auto ValueString = gm->GetStringQuestID();

	FName ValueName( *ValueString );
	QuestID = ValueName;
	UE_LOG( LogTemp , Error , TEXT( "BeginPlay() GameMode: %s" ) , *QuestID.ToString() );

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

	//QuestLogComp 에서 생성되고, QuestId를 받음.
	QuestLogComponent = ProjectDCharacter->FindComponentByClass<UQuestLogComponent>();
	/*if (QuestLogComponent)
	{
		//컴포넌트에서 questID 방송 받아서 여기서 함수 호출해서 QuestID 저장하기
		QuestLogComponent->OnQuestDataLoaded.AddDynamic( this , &AQuest_Base::OnQuestDataLoadedHandler );
	}*/

	ProjectDCharacter->OnObjectiveIDCalled.RemoveDynamic(this , &AQuest_Base::OnObjectiveIDHeard );
	ProjectDCharacter->OnObjectiveIDCalled.AddDynamic( this , &AQuest_Base::OnObjectiveIDHeard );

	/*AsyncTask( ENamedThreads::GameThread , [this]() {
		while (QuestID.IsNone())
		{
			FPlatformProcess::Sleep( 0.1f ); // 설정될 때까지 0.1초 간격으로 대기
		}

		UE_LOG( LogTemp , Error , TEXT( "GetQuestDetails() , CheckItem()" ) )

		// QuestID가 유효해졌으므로 이후 작업 수행
		GetQuestDetails();
		CheckItem();
		ReadyAddTracker.Broadcast();
	} );*/
	//비동기 함수!!! ->Tick으로

	//딜레이 0.1초
	QuestLogComponent->UpdateCurrentActiveQuest.RemoveDynamic( this , &AQuest_Base::CurrentActiveQuest );
	QuestLogComponent->UpdateCurrentActiveQuest.AddDynamic( this , &AQuest_Base::CurrentActiveQuest);
}


// Called every frame
void AQuest_Base::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	/*if (!bQuestIDValid)
	{
		if (QuestID.IsValid())
		{
			UE_LOG( LogTemp , Error , TEXT( "QuestBase (FName QuestID): %s" ) , *QuestID.ToString() );

			// QuestID가 유효해졌으므로 이후 작업 수행
			GetQuestDetails();
			CheckItem();
			ReadyAddTracker.Broadcast();

			IsCompleted = AreObjectivesComplete();

			bQuestIDValid = true;
		}
	}*/
	
	
}

void AQuest_Base::OnObjectiveIDHeard( FString BObjectiveID , int32 Value )
{
	UE_LOG( LogTemp , Warning , TEXT( "AQuest_Base::OnObjectiveIDHeard - %s , %d" ) , *BObjectiveID , Value );

	//여기서 드롭했을 경우 그 값을 목표에 적용하도록 해놓은 것이다!
	int32* ValuePtr = CurrentObjectiveProgress.Find( BObjectiveID );

	if (ValuePtr)
	{
		int32 Sign = FMath::Sign( Value );
		if (Sign > 0)
		{
			if (GetObjectiveDataByID( BObjectiveID ).Quantity > *ValuePtr)
			{
				int32 PluValue = *ValuePtr + Value;
				CurrentObjectiveProgress.Add( BObjectiveID , PluValue );
				IsObjectiveComplete( BObjectiveID );
				//Tracker Widget에 보내는 델리게이트
				OnObjectiveHeard.Broadcast();
				return;
			}
		}
		else
		{
			int32 PluValue = *ValuePtr + Value;
			CurrentObjectiveProgress.Add( BObjectiveID , PluValue );
			return;
		}
	}
	else
	{
		return;
	}
}

void AQuest_Base::GetQuestDetails()
{
	//Tracker 생성
	UE_LOG( LogTemp , Error , TEXT( "GetQuestDetails(): %s" ) , *QuestID.ToString() );

	//ReadyAddTracker.Broadcast();

	if (!QuestData.DataTable)
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / QuestData.DataTable is nullptr" ) );
		return;
	}

	if (QuestID.IsNone())
	{
		UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ GetQuestDetails AQuest_Base" ) );
	}

	//UE_LOG( LogTemp , Error , TEXT( "GetQuestDetails(): %s" ) , *QuestID.ToString() );
	
	FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );
	if (!Row)
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / !Row" ) );
		return;
	}

	QuestDetails = *Row;

	// Gamemode에 다음 진행할 퀘스트ID 보냄
	gm->SetNxtQuestID( *QuestDetails.NextQuestID );

	if (CurrentStage >= QuestDetails.Stages.Num())
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / CurrentStage is out of bounds" ) );
		return;
	}

	//현재 퀘스트 Stage를 CurrnetStageDetails 에 저장. 아래가 CurrentObjectiveProgress도 넣는 것.
	CurrentStageDetails = QuestDetails.Stages[CurrentStage];

	CurrentObjectiveProgress.Reset();

	for (const auto& Objective : CurrentStageDetails.Objectives)
	{
		CurrentObjectiveProgress.Add( Objective.ObjectiveID , 0 );
		UE_LOG( LogTemp , Error , TEXT( "CurrentObjectiveProgress.Add : %s" ), *Objective.ObjectiveID );
	}

	/*Gamemode 에 QuestID 전송
	auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	FString NameString = QuestID.ToString();
    int32 intQuestID =  FCString::Atoi(*NameString);
	gm->SetQuestID( intQuestID );*/

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {

		} ,
		1.0f , // 지연 시간(초)
		false
		);
	
	QuestLogComponent->AddToTracker();

}


void AQuest_Base::CheckItem()
{
	UInventoryComponent* Inventorycomponent = ProjectDCharacter->FindComponentByClass<UInventoryComponent>();

	if (Inventorycomponent) {
		UE_LOG( LogTemp , Error , TEXT( "QuestInventorycomponent 존재" ) );

		for (const auto& Objective : CurrentStageDetails.Objectives)
		{
			if (Objective.Type == EObjectiveType::Collect)
			{
				int32 InventoryCount = Inventorycomponent->FindItemQuantity( Objective.ObjectiveID );
				UE_LOG( LogTemp , Error , TEXT( "Objective.ObjectiveID : %s / InventoryCount : %d" ) , *Objective.ObjectiveID , InventoryCount );

				// 인벤토리에 해당 아이템이 있을 때에만 호출
				if (InventoryCount > 0)
				{
					OnObjectiveIDHeard( Objective.ObjectiveID , InventoryCount );
				}
			}
		}
	}
}

void AQuest_Base::OnQuestDataLoadedHandler( FName BroQuestID )
{
	QuestID = BroQuestID;
}


//WidgetQuestNotification위젯 생성!!
void AQuest_Base::IsObjectiveComplete(FString ObjectiveID)
{
	int32* ValuePtr = CurrentObjectiveProgress.Find( ObjectiveID );

	if (ValuePtr && (*ValuePtr >= GetObjectiveDataByID( ObjectiveID ).Quantity))
	{
		UWidgetQuestNotification* QuestWidget = CreateWidget<UWidgetQuestNotification>( GetWorld() , Notification_Widget );

		if (QuestWidget)
		{
			QuestWidget->ObjectiveText = GetObjectiveDataByID( ObjectiveID ).Description;
			QuestWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Quest) );
			//IsCompleted = AreObjectivesComplete();
			//if (IsCompleted)
				//UE_LOG( LogTemp , Error , TEXT( "IsCompleted = true;" ) );

			//남은 stage가 있는지 모두 다 완료했는지 확인
			if (AreObjectivesComplete())
			{
				CurrentStage += 1;
				if (QuestDetails.Stages.IsValidIndex( CurrentStage ))
				{
					UE_LOG( LogTemp , Error , TEXT( "CurrentStage ++ " ) );
					GetQuestDetails();
					CheckItem();
				}
				else {
					IsCompleted = true;
					if (QuestDetails.AutoComplete) {
						UE_LOG( LogTemp , Error , TEXT( "IsObjectiveComplete(FString ObjectiveID) QuestDetails.AutoComplete." ) );
						QuestLogComponent = ProjectDCharacter->FindComponentByClass<UQuestLogComponent>();
						QuestLogComponent->TurnInQuest( QuestID );
						//QuestLogComponent->CompleteQuest( QuestID );
					}
				}
			}
		}
	}
}

bool AQuest_Base::AreObjectivesComplete()
{
	for (auto& Objective : CurrentStageDetails.Objectives)
	{
		FObjectiveDetails ObjectiveData = GetObjectiveDataByID( Objective.ObjectiveID );

		// 현재 진행 상황 찾기
		int32* CurrentProgress = CurrentObjectiveProgress.Find( Objective.ObjectiveID );

		// 목표 데이터와 현재 진행 상황이 유효한지 확인
		if (ObjectiveData.Quantity > 0 && CurrentProgress)
		{
			// 목표 수량과 현재 진행 상황 비교
			if (*CurrentProgress >= ObjectiveData.Quantity)
			{
				Local_AllComplete = true;
			}
			else
			{
				Local_AllComplete = false;
				break; // 하나라도 목표 달성 조건을 만족하지 않으면 반복문 종료
			}
		}
		else
		{
			Local_AllComplete = false;
			break; // 목표 데이터나 현재 진행 상황이 유효하지 않으면 반복문 종료
		}
	}

	return Local_AllComplete;
}

void AQuest_Base::CurrentActiveQuest()
{
	GetQuestDetails();
	CheckItem();
	IsCompleted = AreObjectivesComplete();
}

FObjectiveDetails AQuest_Base::GetObjectiveDataByID( FString ObjectiveID )
{
	for (const auto& Objective : CurrentStageDetails.Objectives)
	{
		if (Objective.ObjectiveID == ObjectiveID) {
			return Objective;
		}
	}
	return FObjectiveDetails();
}