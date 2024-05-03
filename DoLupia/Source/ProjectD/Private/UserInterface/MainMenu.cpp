// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/MainMenu.h"

#include "Characters/ProjectDCharacter.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	SetKeyboardFocus();

	PlayerCharacter = Cast<AProjectDCharacter>(GetOwningPlayerPawn());
}

FReply UMainMenu::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::I)
    {
		APlayerController* PC = Cast<APlayerController>(PlayerCharacter->GetController());

		if (GetVisibility() == ESlateVisibility::Visible)
		{
			SetVisibility(ESlateVisibility::Collapsed);

			const FInputModeGameAndUI InputMode;
			PC->SetInputMode(InputMode);
		}

        return FReply::Handled();
    }

    return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}


bool UMainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	// �÷��̾ �������� �巡�� �� ��� �� �� �ֵ��� ����
	UItemBase* ItemBase = ItemDragDrop->GetSourceItem();
	if(PlayerCharacter && ItemBase)
	{
		PlayerCharacter->DropItem(ItemBase, ItemBase->GetQuantity());
		return true;
	}

	return false;
}
