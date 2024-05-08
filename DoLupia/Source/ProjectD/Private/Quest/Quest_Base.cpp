// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Quest_Base.h"
#include "Quest/QuestLogComponent.h"
#include <Characters/ProjectDCharacter.h>

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
	auto ProjectDCharacter = Cast<AProjectDCharacter>( PlayerCharacter );
	if (!IsValid( ProjectDCharacter ))
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / ProjectDCharacter is not valid." ) );
		return;
	}

	//QuestLogComp 에서 생성되고, QuestId를 받는데, beginplay 에서도, 함수에서도 invalid하다....
	UQuestLogComponent* Questcomponent = ProjectDCharacter->FindComponentByClass<UQuestLogComponent>();
	if (Questcomponent) 
	{
		//컴포넌트에서 questID 방송 받아서 여기서 함수 호출해서 QuestID 저장하기
		UE_LOG( LogTemp , Error , TEXT( "&AQuest_Base::OnQuestDataLoadedHandler." ) );
		Questcomponent->OnQuestDataLoaded.AddDynamic( this , &AQuest_Base::OnQuestDataLoadedHandler );
	}
	

	ProjectDCharacter->OnObjectiveIDCalled.AddDynamic( this , &AQuest_Base::OnObjectiveIDHeard );
	
	GetQuestDetails();
}


// Called every frame
void AQuest_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuest_Base::OnObjectiveIDHeard(FString BObjectiveID)
{
	int32* ValuePtr = CurrentObjectiveProgress.Find( BObjectiveID );

	if (ValuePtr)
	{
		if (GetObjectiveDataByID( BObjectiveID ).Quantity > *ValuePtr) {
			// 해당 키를 찾은 경우
			int32 Value = *ValuePtr + 1;
			CurrentObjectiveProgress.Add( BObjectiveID , Value );

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
	UE_LOG( LogTemp , Error , TEXT( "QuestID: %s" ) , *QuestID.ToString() );

	
	FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );
	if (!Row)
	{
		UE_LOG( LogTemp , Error , TEXT( "Quest_Base / GetQuestDetails / !Row" ) );
		return;
	}
	// 나머지 코드

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
	UE_LOG( LogTemp , Error , TEXT( "QuestID: %s AQuest_Base::OnQuestDataLoadedHandler( FName BroQuestID )" ) , *QuestID.ToString() );
}

/*FObjectiveDetails AQuest_Base::GetObjectiveDataByID(FString ObjectiveID)
{
	for (const auto& Objective : CurrentStageDetails.Objectives)
	{
		if (Objective.ObjectiveID == ObjectiveID) {
			return Objective;
		}
	}
}
*/


/*
LogTemp: Error: &AQuest_Base::OnQuestDataLoadedHandler. //스폰 되고
LogTemp: Error: Invalid QuestID _ GetQuestDetails AQuest_Base // 전달이 안됐고
LogTemp : Error: QuestID: None // GetQuestDetails() 여기가 불려서 안되고
LogDataTable : Warning: UDataTable::FindRow : 'Searching for row' requested invalid row 'None' from DataTable '/Game/QuestSystem/QuestData.QuestData'.
LogTemp : Error : Quest_Base / GetQuestDetails / !Row 
LogTemp : Error: QuestID: 1001 SpawneQuest->QuestID // logComp 에서 프라퍼티 적용이 되는..
어케 해야해?
*/