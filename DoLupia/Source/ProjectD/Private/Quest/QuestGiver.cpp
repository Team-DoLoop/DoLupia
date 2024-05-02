// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/QuestGiver.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/ProjectDGameMode.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UQuestGiver::UQuestGiver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ������ ���̺� �ε�
	UDataTable* DataTable = Cast<UDataTable>(StaticLoadObject(
		UDataTable::StaticClass(),
		nullptr,
		TEXT("/Game/QuestSystem/QuestDataTable.QuestDataTable")
	));
	if (DataTable)
	{
		// ������ ���̺��� ���������� �ε�� ��� �۾� ����
		QuestData.DataTable = DataTable;  // ������ ���̺� ����
		//QuestData.RowName = FName("DefaultRow");  // �� �̸� ����
	}
	else
	{
		// �ε� ���� �� ó��
		UE_LOG(LogTemp, Error, TEXT("Data table not found!"));
	}

	UWorld* World = GetWorld();
	if (!World) return;

	// �÷��̾� ĳ���͸� �����ɴϴ�.
	MyPlayerCharacter = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(World, 0));

	MyGameMode = Cast<AProjectDGameMode>(UGameplayStatics::GetGameMode(World));
}


// Called when the game starts
void UQuestGiver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuestGiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestGiver::DisplayQuest()
{

}

/*FString UQuestGiver::InteractWith()
{
	auto QuestComponent = MyPlayerCharacter->GetComponentByClass(UQuestGiver::StaticClass());

	//QuestComponent->QueryActiveQuest()
}
*/
