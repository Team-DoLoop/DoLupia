
#include "Components/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


UItemBase* UInventoryComponent::FindMatchItem(UItemBase* ItemIn) const
{
	if(ItemIn)
	{
		// �������� �迭�ȿ� �����ϸ� ��ȯ�Ѵ�.
		if(InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}

	return nullptr;
}

UItemBase* UInventoryComponent::FindNextItemByID(UItemBase* ItemIn) const
{
	if(ItemIn)
	{
		// �迭�� ������ ID�� ã�� ��Ҹ� ��ȯ��Ŵ.
		// -> ** �̱� ������ �������� ��ȯ����. <TObjectPtr>::ElementType*
		if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}

	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	// ���ٽ����� ����������Ʈ ����
	// ��ȸ�ϸ鼭 ���� ID�� ���ų� ������ �� ä�������� �ʴٸ� ����� ��ȯ�Ѵ�.
	// �� �� ItemIn�� ������ �ʹ� ũ�ٸ� ���� �� �޾ƾ� �ϱ� ������ ��͸� ��������.
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = 
		InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
		{
			return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
		}))
	{
		return *Result;
	}

	return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->NumericData.Weight);

	if(WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}

	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount)
{
	const int32 AddAmountToMakeFullStack = StackableItem->NumericData.MaxStackSize - StackableItem->Quantity;

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);

	ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountToRemove);

	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	if(!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

FItemAddResult UInventoryComponent::HandelNonStackableItems(UItemBase* InputItem)
{
	const float StackWeigt = InputItem->GetItemStackWeight();
	// ���� �������� ���԰� �ִ� �� üũ
	if(FMath::IsNearlyZero(StackWeigt) || StackWeigt < 0)
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. Item has invalid weight value."), InputItem->GetTextData().Name));
	}

	// ���� ���Ը� �߰��� �� ���԰� �ʰ��ȴٸ� �߰����� �ʴ´�.
	if(InventoryTotalWeight + StackWeigt > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. Item would overflow weight limit."), InputItem->GetTextData().Name));
	}

	// ���� �κ��丮�� �� á�ٸ� �߰����� �ʴ´�.
	if(InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. All invetory slots are full."), InputItem->GetTextData().Name));
	}

	AddNewItem(InputItem, 1);

	return FItemAddResult::AddedAll(1, FText::Format
	(FText::FromString("Successfully added a single {0} to the Inventory."), InputItem->GetTextData().Name));
}

int32 UInventoryComponent::HandelStackableItems(UItemBase* InputItem, int32 RequestedAddAmount)
{
	return 0;
}

FItemAddResult UInventoryComponent::HandelAddItem(UItemBase* InputItem)
{
	if(GetOwner())
	{
		const int32 InitialRequestedAddAmount = InputItem->Quantity;

		// ���ÿ� ������ �ʴ� ������ ��ȯ ex) ����, �� ��
		if(!InputItem->NumericData.bIsStackable)
		{
			return HandelNonStackableItems(InputItem);
		}

		// ���ÿ� ���̴� ������ ��ȯ ex) �Һ� ������ ��
		const int32 StackableAmountAdded = HandelStackableItems(InputItem, InitialRequestedAddAmount);

		if(StackableAmountAdded == InitialRequestedAddAmount)
		{
			// return ��� ��ȯ
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Successfully added {0} {1} to the Inventory."), 
			InitialRequestedAddAmount, InputItem->GetTextData().Name));
			
		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			// �κ� ��ȯ
			return FItemAddResult::AddedPartial(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Partial amount of {0} added to thie Inventory. Number added {1}"), 
			InputItem->GetTextData().Name, InitialRequestedAddAmount));
		}

		if(StackableAmountAdded <= 0)
		{
			// none ��ȯ
			return FItemAddResult::AddedNone(FText::Format
			(FText::FromString("Count not add {0} to the Inventory. No remaining inventory slots, or invalid item."), 
			InputItem->GetTextData().Name));
		}
	}

	//Owner�� ���� �� ������Ʈ�� �ٿ��Ų��.
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed"));
	
}


void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;

	// ���� ������ ���� ���� �̹� ��	���丮 �޸� �� ���� �����Ͱ� ������ ���� ItemCopy�� ��Ű�� �ʴ´�. 
	if(Item->bIsCopy || Item->bIsPickup)
	{
		// ������ �ִ� �׸��� �÷��׵鸸 �����Ѵ�.
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		// �ٸ� �κ��丮 �Ǵ� ó�� ������� �����͸� ī���Ѵ�.
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast();
}

