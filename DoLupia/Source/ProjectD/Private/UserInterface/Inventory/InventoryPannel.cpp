
//game
#include "UserInterface/Inventory/InventoryPannel.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/InventoryComponent.h"


#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

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
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), 
		InventoryReference->GetInventoryTotalWeight(), 
		InventoryReference->GetWeightCapacity()));

	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
		InventoryReference->GetInventoryContents().Num(),
		InventoryReference->GetSlotCapacity()));
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
	}
}


bool UInventoryPannel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
