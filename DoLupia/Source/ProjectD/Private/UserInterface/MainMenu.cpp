// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"

#include "Characters/ProjectDCharacter.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AProjectDCharacter>(GetOwningPlayerPawn());
}

bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// 플레이어가 아이템을 드래그 앤 드랍 할 수 있도록 설정
}
