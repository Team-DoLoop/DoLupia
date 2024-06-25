// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/AutoQuestAcceptActor.h"
#include "Engine/DataTable.h"
#include <Characters/ProjectDCharacter.h>
#include <Kismet/GameplayStatics.h>
#include "Quest/QuestLogComponent.h"
#include <Components/BoxComponent.h>

#include "Gamemode/PlayerGameMode.h"

// Sets default values
AAutoQuestAcceptActor::AAutoQuestAcceptActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComponent" ) );

	UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/Data/QuestDataTable.QuestDataTable" ) );
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

	//이 액터를 깔아두고, 레벨 시작이나, 충돌할때, 저 함수를 실행시키면 되는거 같음.GiveQuest를
}

// Called when the game starts or when spawned
void AAutoQuestAcceptActor::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AAutoQuestAcceptActor::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	UWorld* World = GetWorld();
	if (!World) return;

	MyPlayerCharacter = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( World , 0 ) );


	FFileHelper::SaveStringToFile( L"AAutoQuestAcceptActor::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void AAutoQuestAcceptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAutoQuestAcceptActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor) {
		AProjectDCharacter* player = Cast<AProjectDCharacter>( OtherActor );
		if (player) {

			GiveQuest();
		}
	}

	this->AutoQuestDestroy();
}

void AAutoQuestAcceptActor::GiveQuest()
{
	if (!MyPlayerCharacter)
		return;

	UQuestLogComponent* Questcomponent = MyPlayerCharacter->FindComponentByClass<UQuestLogComponent>();

	bool ActiveQuest = Questcomponent->QueryActiveQuest( QuestData.RowName );
	bool CompleteQuest = Questcomponent->QueryCompleteQuests( QuestData.RowName );
	if (!ActiveQuest&&!CompleteQuest) {

		auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
		FString tmpString = QuestData.RowName.ToString();

		 //겜모에 퀘스트 아이디 string 로 넘김.
		gm->SetStringQuestID( tmpString );
		Questcomponent->AddNewQuest( QuestData.RowName );
		
	}
}

void AAutoQuestAcceptActor::AutoQuestDestroy()
{
	this->Destroy();
}

