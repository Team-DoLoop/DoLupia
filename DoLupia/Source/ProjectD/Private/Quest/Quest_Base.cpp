// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Quest_Base.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/QuestInventoryComponent.h" //지울 예정 
#include <Characters/ProjectDCharacter.h>
#include "Data/WidgetData.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Characters/Components/InventoryComponent.h"
#include "UserInterface/Quest/WidgetQuestNotification.h"

// Sets default values
AQuest_Base::AQuest_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/QuestDataTable.QuestDataTable" ) );

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
	static ConstructorHelpers::FClassFinder<UWidgetQuestNotification> WidgetClassFinder( TEXT( "/Game/QuestSystem/WBP_WidgetQuestNotification.WBP_WidgetQuestNotification_C" ) );
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
	UQuestLogComponent* Questcomponent = ProjectDCharacter->FindComponentByClass<UQuestLogComponent>();
	if (Questcomponent) 
	{
		//컴포넌트에서 questID 방송 받아서 여기서 함수 호출해서 QuestID 저장하기
		Questcomponent->OnQuestDataLoaded.AddDynamic( this , &AQuest_Base::OnQuestDataLoadedHandler );
	}

	ProjectDCharacter->OnObjectiveIDCalled.AddDynamic( this , &AQuest_Base::OnObjectiveIDHeard );


	//비동기 함수!!!
	AsyncTask( ENamedThreads::GameThread , [this]() {
		while (QuestID.IsNone())
		{
			FPlatformProcess::Sleep( 0.1f ); // 설정될 때까지 0.1초 간격으로 대기
		}

		UE_LOG( LogTemp , Error , TEXT( "GetQuestDetails() , CheckItem()" ) )

		// QuestID가 유효해졌으므로 이후 작업 수행
		GetQuestDetails();
		CheckItem();

	} );

	IsCompleted = AreObjectivesComplete();
}


// Called every frame
void AQuest_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest_Base::OnObjectiveIDHeard( FString BObjectiveID , int32 Value )
{
	UE_LOG( LogTemp , Warning , TEXT( "AQuest_Base::OnObjectiveIDHeard - %s , %d" ) , *BObjectiveID , Value );

	//여기서 드롭했을 경우 그 값을 목표에 적용하도록 해놓은 것이다!!!! 인벤토리와 연결해야할 부분이 있을듯
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
	if (!QuestData.DataTable)
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / QuestData.DataTable is nullptr" ) );
		return;
	}

	if (QuestID.IsNone())
	{
		UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ GetQuestDetails AQuest_Base" ) );
	}

	
	FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );
	if (!Row)
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / !Row" ) );
		return;
	}

	QuestDetails = *Row;

	if (CurrentStage >= QuestDetails.Stages.Num())
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / CurrentStage is out of bounds" ) );
		return;
	}

	CurrentStageDetails = QuestDetails.Stages[CurrentStage];

	CurrentObjectiveProgress.Reset();

	for (const auto& Objective : CurrentStageDetails.Objectives)
	{
		CurrentObjectiveProgress.Add( Objective.ObjectiveID , 0 );
		UE_LOG( LogTemp , Error , TEXT( "CurrentObjectiveProgress.Add : %s" ), *Objective.ObjectiveID );
	}
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
			QuestWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Quest));
			IsCompleted = AreObjectivesComplete();
			if(IsCompleted)
				UE_LOG( LogTemp , Error , TEXT( "IsCompleted = true;" ) );
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

FObjectiveDetails AQuest_Base::GetObjectiveDataByID( FString ObjectiveID )
{
	for (const auto& Objective : CurrentStageDetails.Objectives)
	{
		if (Objective.ObjectiveID == ObjectiveID) {
			return Objective;
		}
	}
	// 목표 ID와 일치하는 항목을 찾지 못한 경우 기본값을 반환하거나 오류 처리를 수행할 수 있습니다.
	return FObjectiveDetails();
}