// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/Dialogsystem/DialogComponent.h"

#include "Blueprint/UserWidget.h"
#include "Data/DialogData.h"

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
		DialogueWidget = CreateWidget<UUserWidget>( GetWorld() , DialogueWidgetClass );

		if (DialogueWidget)
		{
			DialogueWidget->AddToViewport();
		}
	}
}


// Called every frame
void UDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogComponent::StartDialog(const FString& NPCNmae, int32 StartubgDialogID)
{
	CurrentNPCName = NPCNmae;
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
		//이게 npc의 마지막 대화이면 Dialog 위젯을 닫는다.
		if (DialogueWidget)
		{
			DialogueWidget->RemoveFromViewport();
		}
		return;
	}

	if (DialogueDataTable)
	{
		static const FString ContextString( TEXT( "GENERAL" ) );
		FDialogueData* DialogueData = DialogueDataTable->FindRow<FDialogueData>( FName( *FString::FromInt( DialogueID ) ) , ContextString );

		if (DialogueData)
		{
			CurrentDialogue = DialogueData;
			CurrentDialogueID = DialogueID;

			if (DialogueWidget)
			{
				FText DialogueText = FText::FromString( CurrentDialogue->DialogueText );
				FText SpeakerText = FText::FromString( CurrentDialogue->Speaker );

				UFunction* UpdateDialogueTextFunction = DialogueWidget->FindFunction( FName( "UpdateDialogueText" ) );
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
}

