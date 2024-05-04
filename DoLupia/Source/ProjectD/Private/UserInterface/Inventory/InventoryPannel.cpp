
//game
#include "UserInterface/Inventory/InventoryPannel.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/Button.h"


#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
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
			for (int i = 0; i < 100; ++i) // test
				//for(int i = 0; i < InventoryReference->GetSlotCapacity(); ++i)
			{
				InventoryReference->AddInventoryContents(nullptr);

				RefreshInventory();
			}

			InventoryReference->OnInventoryUpdated.AddUObject(this, &UInventoryPannel::SetInfoText);
		}
	}

	SortButton->OnClicked.AddDynamic(this, &UInventoryPannel::SortItem);
}


void UInventoryPannel::SetInfoText() const
{
	const FString& WeightInfoValue {
		FString::Printf(TEXT("%.2f"), InventoryReference->GetInventoryTotalWeight()) + "/" +
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

		const TArray<UItemBase*> InventoryContents = InventoryReference->GetInventoryContents();

		for(int32 i = 0; i < InventoryContents.Num(); ++i)
		{
			UInventoryItemSlot* ItemSlot = CreateWidget<UInventoryItemSlot>(this, InventorySlotFactory);

			ItemSlot->SetItemReference( InventoryContents[i] );
			ItemSlot->ResetItemSlot();
			ItemSlot->SetSlotIndex(i);


			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}
	}
}

void UInventoryPannel::RefreshInventoryPannel(const int32 Index, UItemBase* ItemIn)
{
	UInventoryItemSlot* ItemSlot = Cast<UInventoryItemSlot>(InventoryPanel->GetChildAt(Index));

	if(!ItemSlot)
		check(false);

	if(!ItemIn)
	{
		if(ItemSlot->GetItemReference())
			ItemSlot->ResetItemSlot();

		return;
	}

	ItemSlot->SetItemReference(ItemIn);
	ItemSlot->RefreshItemSlot();

	UInventoryTooltip* ToolTip = ItemSlot->GetToolTip();

	if(ToolTip)
	{
		ToolTip->SetupTooltip();
		SetInfoText();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UInventoryPannel::RefreshInventoryPannel : ToolTip is null"));
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

void UInventoryPannel::SortItem()
{
	InventoryReference->SortItem_Name();

	//if (InventoryReference)
	//{
	//	ESortType ItemSortType = static_cast<ESortType>(SortType);

	//	switch (ItemSortType)
	//	{
	//	case ESortType::Sort_Name:
	//		InventoryReference->SortItem_Name();
	//		break;
	//	case ESortType::Sort_Type:

	//		break;
	//	case ESortType::Sort_Grade:

	//		break;
	//	default:;
	//	}
	//}
		

	
}
