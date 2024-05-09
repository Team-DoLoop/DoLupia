// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Quest_Base.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/QuestInventoryComponent.h"
#include <Characters/ProjectDCharacter.h>
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Quest/WidgetQuestNotification.h"

// Sets default values
AQuest_Base::AQuest_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		UE_LOG( LogTemp , Error , TEXT( "Data table not found!" ) );
	}

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

	//테스트 퀘스트 인벤토리 컴포넌트 생성
	UQuestInventoryComponent* QuestInventorycomponent = ProjectDCharacter->FindComponentByClass<UQuestInventoryComponent>();

	if (QuestInventorycomponent) {

		for (const auto& Objective : CurrentStageDetails.Objectives)
		{
			//목표들 중에 수집이 있는지 확인하고, 인벤토리에 있는지 확인하는
			if (Objective.Type == EObjectiveType::Collect)
			{
				FName MyName = FName( Objective.ObjectiveID );
				int32 InventoryCount = QuestInventorycomponent->QueryInventory( MyName );
				
				//목표 수량에 보내기
				for (const auto& Objective : CurrentStageDetails.Objectives)
					OnObjectiveIDHeard( Objective.ObjectiveID , InventoryCount );
			}
		}
	}

	ProjectDCharacter->OnObjectiveIDCalled.AddDynamic( this , &AQuest_Base::OnObjectiveIDHeard );


	//비동기 함수!!!
	AsyncTask( ENamedThreads::GameThread , [this]() {
		while (QuestID.IsNone())
		{
			FPlatformProcess::Sleep( 0.1f ); // 설정될 때까지 0.1초 간격으로 대기
		}

		// QuestID가 유효해졌으므로 이후 작업 수행
		GetQuestDetails();
	} );
}


// Called every frame
void AQuest_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest_Base::OnObjectiveIDHeard(FString BObjectiveID, int32 Value )
{
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
			QuestWidget->AddToViewport();
		}
	}
}
