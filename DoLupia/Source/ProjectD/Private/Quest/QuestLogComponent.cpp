// Fill out your copyright notice in the Description page of Project Settings.

#include "Quest/QuestLogComponent.h"
#include "Quest/Quest_Base.h"  // AQuest_Base ���
#include "Quest/QuestInteractionInterface.h"

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestLogComponent::AddNewQuest(FString QuestID)
{
	CurrentActiveQuests.AddUnique(QuestID);

	// ���� ���� ����
	AQuest_Base* SpawnedQuest = GetWorld()->SpawnActor<AQuest_Base>(AQuest_Base::StaticClass());

	//���� ����Ʈ�� ������ ����Ʈ�� �߰�
	CurrentQuest.Add(SpawnedQuest);
}

bool UQuestLogComponent::QueryActiveQuest(FString QuestID)
{
	//���� ����Ʈ�� Ư�� ����Ʈ ���̵� �ִ����� ���� bool ��
	bool QuestExist = CurrentActiveQuests.Contains(QuestID);
	return QuestExist;
}

