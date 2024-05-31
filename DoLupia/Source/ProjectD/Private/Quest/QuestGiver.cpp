// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestGiver.h"

#include <Data/WidgetData.h>

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
#include "Characters/Components/InventoryComponent.h"
#include "World/Pickup.h"

// Sets default values for this component's properties
UQuestGiver::UQuestGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// 데이터 테이블 로드
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
		UE_LOG(LogTemp, Error, TEXT("Data table not found!"));
	}

	// 데이터 테이블 로드
	ItemDataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/ItemData/MundaneItems.MundaneItems" ) );

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
    auto QuestComponent = Cast<UQuestLogComponent>( MyPlayerCharacter->FindComponentByClass( UQuestLogComponent::StaticClass()));
    if (QuestComponent == nullptr)
    {
        return FString( TEXT( "QuestComponent not found or cast failed." ) );
    }

    UE_LOG( LogTemp , Error , TEXT( "QuestData.RowName %s" ) , *QuestData.RowName.ToString() );

    bool ActiveQuest = QuestComponent->QueryActiveQuest( QuestData.RowName );
    bool CompleteQuest = QuestComponent->QueryCompleteQuests( QuestData.RowName );
    bool CompleteQuestTurnedIn = QuestComponent->QueryCompleteQuestsTurnedIn( QuestData.RowName );
    if (!ActiveQuest && !CompleteQuest)
    {
        FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestData.RowName , TEXT( "Searching for row" ) , true );

        if (Row->AutoAccept) {
            //자동으로 AddNewQuest 실행 ( Logcomp 에 있는
            QuestComponent->AddNewQuest( QuestData.RowName );
            return GetOwner()->GetName();
        }
        else {
            //여기서 UWidgetQuestGiver 생성함. QuestID 넘김.
            DisplayQuest(0);
            return GetOwner()->GetName();
        }        
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
            if (CompleteValuePtr->IsCompleted && !CompleteValuePtr->IsTurnedIn && !CompleteQuestTurnedIn)
            {
                UE_LOG( LogTemp , Error , TEXT( "DisplayRewards();" ) );
                //완료가 true이면
                DisplayRewards();
                return GetOwner()->GetName();
            }
            /*
            else 
            {
                UE_LOG( LogTemp , Error , TEXT( " DisplayQuest(CompleteValuePtr->CurrnetStage);" ) );
 
                DisplayQuest( CompleteValuePtr->CurrnetStage );
                return GetOwner()->GetName();
            }  
            */
            
        }

        // 모든 조건을 처리한 후에도 값을 반환하지 않았으므로 기본값을 반환합니다.
        return FString( TEXT( "InteractWith function did not return a valid value." ) );
    }
}

void UQuestGiver::DisplayQuest(int32 CurrentStage)
{
    FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestData.RowName , TEXT( "Searching for row" ) , true );

    if (Row)
    {
		QuestWidget = CreateWidget<UWidgetQuestGiver>( GetWorld() , QuestGiverWidget );
        if (QuestWidget)
        {
	        QuestWidget->QuestDetails = *Row;
            QuestWidget->QuestID = QuestData.RowName;
            QuestWidget->CurrentStage = CurrentStage;
			QuestWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Quest)); // 위젯을 화면에 추가
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

            //보상 아이템 들 이름, 수량이 있을 때 보내기
            auto RewardItems = Row->Stages.GetData()->ItemRewards.GetData()->RewardsItem;
            if(!RewardItems.IsEmpty())
            {
	            for (auto& Pair : Row->Stages.GetData()->ItemRewards.GetData()->RewardsItem)
	            {
	                //아이템 종류 선택ID 수량 연동 해야할듯
	                DesiredItemID = FName(Pair.Key);
	                RewardsWidget->ItemRewards.Add(CreateItem( UItemBase::StaticClass() , Pair.Value ));
	            }
            }

            RewardsWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Quest));
        }
    }   
}

UItemBase* UQuestGiver::CreateItem(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
    if (ItemDataTable && !DesiredItemID.IsNone())
    {
        const FItemData* ItemData = ItemDataTable->FindRow<FItemData>( DesiredItemID , DesiredItemID.ToString() );

        ItemReference = NewObject<UItemBase>( this , BaseClass );

        ItemReference->SetID( ItemData->ID );
        ItemReference->SetItemType( ItemData->ItemType );
        ItemReference->SetItemQuality( ItemData->ItemQuality );
        ItemReference->SetItemStatistics( ItemData->ItemStatistics );
        ItemReference->SetTextData( ItemData->TextData );
        ItemReference->SetNumericData( ItemData->NumericData );
        ItemReference->SetAssetData( ItemData->AssetData );

        // 만약 MaxStacksize 가 1보다 작다면 인벤토리에 쌓이지 않게 한다.
        FItemNumericData& ItemNumericData = ItemReference->GetNumericData();
        ItemNumericData.bIsStackable = ItemNumericData.MaxStackSize > 1;
        InQuantity <= 0 ? ItemReference->SetQuantity( 1, false ) : ItemReference->SetQuantity( InQuantity, false );

        //UpdateInteractableData();
        return ItemReference;
    }
    return nullptr;
}
