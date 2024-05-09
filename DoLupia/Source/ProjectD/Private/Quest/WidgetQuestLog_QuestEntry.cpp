// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/WidgetQuestLog_QuestEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Quest/Struct_QuestSystem.h"

void UWidgetQuestLog_QuestEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/QuestData.QuestData" ) );

	if (DataTable)
	{
		QuestData.DataTable = DataTable;
	}
	FQuestDetails* Row = QuestData.DataTable->FindRow<FQuestDetails>( QuestID , TEXT( "Searching for row" ) , true );
	if (Row)
	{
		if (!Row->QuestName.IsEmpty())
		{
			FText QN_MyText = FText::FromString( Row->QuestName );
			txt_QuestName->SetText( QN_MyText );
		}
	}

	if (btn_QuestName)
	{
		btn_QuestName->OnClicked.AddDynamic( this , &UWidgetQuestLog_QuestEntry::OnButtonClicked );
	}
}

void UWidgetQuestLog_QuestEntry::NativeConstruct()
{
	Super::NativeConstruct();

}

void UWidgetQuestLog_QuestEntry::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWidgetQuestLog_QuestEntry::OnButtonClicked()
{
	if (OnQuestSelected.IsBound())
	{
		//퀘스트 로그 위젯으로 보내진다 -> OnQuestSelected
		OnQuestSelected.Broadcast( QuestID , QuestActor ); // 델리게이트 호출
	}
}
