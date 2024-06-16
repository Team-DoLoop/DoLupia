// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Dialogsystem/DialogComponent.h"

#include "Blueprint/UserWidget.h"
#include "Characters/ProjectDCharacter.h"
#include "Data/DialogData.h"
#include "Data/WidgetData.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "NPC/NPCBase.h"
#include "Pooling/SoundManager.h"
#include "Quest/QuestGiver.h"
#include "Quest/TestNPCCharacter.h"
#include "UserInterface/NPC/DialogWidget.h"

// Sets default values for this component's properties
UDialogComponent::UDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CurrentDialogueID = -1;
	CurrentDialogue = nullptr;
	DialogueWidget = nullptr;
}


// Called when the game starts
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogWidget>( GetWorld() , DialogueWidgetClass );
	}
}


// Called every frame
void UDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogComponent::StartDialog(AActor* InCurrentNPC, const FString& NPCID , int32 StartubgDialogID)
{
	CurrentNPC = InCurrentNPC;
	CurrentNPCName = NPCID;

	if (DialogueWidget)
	{
		UFunction* SetCurrentNPCFunction = DialogueWidget->FindFunction( FName( "SetCurrentNPC" ) );
		if (SetCurrentNPCFunction)
		{
			DialogueWidget->ProcessEvent( SetCurrentNPCFunction , &InCurrentNPC );
		}

		ShowDialogWidget();
	}

	LoadDialogue( StartubgDialogID );
	
}

void UDialogComponent::AdvanceDialog()
{
	if (CurrentDialogue)
	{
		if (CurrentDialogue->bTriggersQuest)
		{
			TriggerQuest();
		}

		LoadDialogue( CurrentDialogue->NextID );
	}
}

FString UDialogComponent::GetCurrentSpeaker() const
{
	return CurrentDialogue ? CurrentDialogue->Speaker : FString();
}

FString UDialogComponent::GetCurrentDialogText() const
{
	return CurrentDialogue ? CurrentDialogue->DialogueText : FString();
}

void UDialogComponent::LoadDialogue(int32 DialogueID)
{
	if (DialogueID == -1)
	{
		// NPC 마지막 대화면 Dialog 위젯을 닫음
		if (DialogueWidget)
		{
			DialogueWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			DialogueWidget->RemoveFromParent();
		}

		// PlaeyerCamera 원상복귀
		auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
		float LvCamlength = gm->PlayerCameraboom;
		gm->LerpPlayerCameraLength( LvCamlength );

		return;
	}

	if (DialogueDataTable)
	{
		UE_LOG( LogTemp , Warning , TEXT( "DialogueDataTable" ) );
		static const FString ContextString( TEXT( "GENERAL" ) );
		FDialogueData* DialogueData = DialogueDataTable->FindRow<FDialogueData>( FName( *FString::FromInt( DialogueID ) ) , ContextString );

		if (DialogueData)
		{
			CurrentDialogue = DialogueData;
			CurrentDialogueID = DialogueID;

			if (DialogueWidget)
			{
				//UE_LOG( LogTemp , Warning , TEXT( "%s %s" ), *CurrentDialogue->DialogueText , *CurrentDialogue->Speaker );
				FText DialogueText = FText::FromString( CurrentDialogue->DialogueText );
				FText SpeakerText = FText::FromString( CurrentDialogue->Speaker );

				UFunction* UpdateDialogueTextFunction = DialogueWidget->FindFunction( FName( "UpdateDialogText" ) );
				if (UpdateDialogueTextFunction)
				{
					DialogueWidget->ProcessEvent( UpdateDialogueTextFunction , &DialogueText );
				}

				UFunction* UpdateSpeakerTextFunction = DialogueWidget->FindFunction( FName( "UpdateSpeakerText" ) );
				if (UpdateSpeakerTextFunction)
				{
					DialogueWidget->ProcessEvent( UpdateSpeakerTextFunction , &SpeakerText );
				}
			}
		}
	}
}

void UDialogComponent::TriggerQuest()
{
	// 퀘스트 창 끄기 전 대화창 끄기
	HideDialogWidget();

	// CurrentNPC에서 UQuestComponent를 가져오기
	ANPCBase* npc = Cast<ANPCBase>( CurrentNPC );

	if (npc)
	{
		auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );
		IQuestInteractionInterface* QuestInterface = Cast<IQuestInteractionInterface>( npc );

		if (player)
		{
			// 퀘스트 트리거 로직을 여기에 추가
			FString QuestID = QuestInterface->InteractWith();
			player->OnObjectiveIDCalled.Broadcast( QuestID , 1 );
		}
		else
		{
			UE_LOG( LogTemp , Warning , TEXT( "UQuestComponent not found on NPC" ) );
		}

		// 퀘스트 받은 npc는 숨기기
		npc->HideNPC();
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT( "CurrentNPC is null" ) );
	}

}

void UDialogComponent::ShowDialogWidget()
{
	if(DialogueWidget && !DialogueWidget->IsInViewport() )
	{
		DialogueWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
		DialogueWidget->SetVisibility( ESlateVisibility::Visible );
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor( true );
	}
}

void UDialogComponent::HideDialogWidget()
{
	if (DialogueWidget && DialogueWidget->IsInViewport())
	{
		DialogueWidget->RemoveFromParent();

		ASoundManager* SoundManager = ASoundManager::GetInstance( GetWorld() );

		SoundManager->StopSound( ENPCSound::NPCSound1 );
		SoundManager->StopSound( ENPCSound::NPCSound2 );
	}
}

