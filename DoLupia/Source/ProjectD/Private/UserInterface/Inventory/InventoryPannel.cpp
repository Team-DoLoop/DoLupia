
//game
#include "UserInterface/Inventory/InventoryPannel.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/InventoryComponent.h"


#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

void UInventoryPannel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<AProjectDCharacter>(GetOwningPlayerPawn());

	if(PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();

		if(InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPannel::RefreshInventory);
			SetInfoText();
		}
	}
}


void UInventoryPannel::SetInfoText() const
{
	const FString& WeightInfoValue {
		FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight()) + "/" +
		FString::SanitizeFloat(InventoryReference->GetWeightCapacity())
	};

	const FString& CapacityInfoValue{
		FString::SanitizeFloat(InventoryReference->GetInventoryContents().Num()) + "/" +
		FString::SanitizeFloat(InventoryReference->GetSlotCapacity())
	};

	WeightInfo->SetText(FText::FromString(WeightInfoValue));
	CapacityInfo->SetText(FText::FromString(CapacityInfoValue));
}

void UInventoryPannel::RefreshInventory()
{
	if(InventoryReference && InventorySlotFactory)
	{
		InventoryPanel->ClearChildren();

		for(UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotFactory);
			ItemSlot->SetItemReference(InventoryItem);

			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}

		SetInfoText();
	}
}


bool UInventoryPannel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(ItemDragDrop->GetSourceItem() && InventoryReference)
	{
		return true;
	}

	return false;
}
