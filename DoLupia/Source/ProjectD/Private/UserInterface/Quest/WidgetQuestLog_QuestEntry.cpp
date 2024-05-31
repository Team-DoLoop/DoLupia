﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/WidgetQuestLog_QuestEntry.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Quest/Struct_QuestSystem.h"

void UWidgetQuestLog_QuestEntry::NativePreConstruct()
{
	Super::NativePreConstruct();

	UDataTable* DataTable = LoadObject<UDataTable>( nullptr , TEXT( "/Game/QuestSystem/Data/QuestDataTable.QuestDataTable" ) );

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

	if (btn_Track)
	{
		btn_Track->OnClicked.AddDynamic(this, &UWidgetQuestLog_QuestEntry::OnTrackButtonClicked);
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

void UWidgetQuestLog_QuestEntry::OnTrackButtonClicked()
{
	if (OnTracked.IsBound()) {

		OnTracked.Broadcast(QuestActor);
	}
}
