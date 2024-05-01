
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
		// 아이템이 배열안에 존재하면 반환한다.
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
		// 배열의 고유의 ID를 찾아 요소를 반환시킴.
		// -> ** 이기 때문에 역참조로 반환하자. <TObjectPtr>::ElementType*
		if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}

	return nullptr;
}

UItemBase* UInventoryComponent::FindNextPartialStack(UItemBase* ItemIn) const
{
	// 람다식으로 프리디케이트 구성
	// 순회하면서 만약 ID가 같거나 스택이 다 채워져있지 않다면 결과를 반환한다.
	// 이 때 ItemIn의 스택이 너무 크다면 여러 번 받아야 하기 때문에 재귀를 수행하자.
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
	// 들어가는 아이템의 무게가 있는 지 체크
	if(FMath::IsNearlyZero(StackWeigt) || StackWeigt < 0)
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. Item has invalid weight value."), InputItem->GetTextData().Name));
	}

	// 만약 무게를 추가할 때 무게가 초과된다면 추가하지 않는다.
	if(InventoryTotalWeight + StackWeigt > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. Item would overflow weight limit."), InputItem->GetTextData().Name));
	}

	// 만약 인벤토리가 다 찼다면 추가하지 않는다.
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

		// 스택에 쌓이지 않는 아이템 반환 ex) 무기, 방어구 등
		if(!InputItem->NumericData.bIsStackable)
		{
			return HandelNonStackableItems(InputItem);
		}

		// 스택에 쌓이는 아이템 반환 ex) 소비 아이템 등
		const int32 StackableAmountAdded = HandelStackableItems(InputItem, InitialRequestedAddAmount);

		if(StackableAmountAdded == InitialRequestedAddAmount)
		{
			// return 모두 반환
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Successfully added {0} {1} to the Inventory."), 
			InitialRequestedAddAmount, InputItem->GetTextData().Name));
			
		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			// 부분 반환
			return FItemAddResult::AddedPartial(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Partial amount of {0} added to thie Inventory. Number added {1}"), 
			InputItem->GetTextData().Name, InitialRequestedAddAmount));
		}

		if(StackableAmountAdded <= 0)
		{
			// none 반환
			return FItemAddResult::AddedNone(FText::Format
			(FText::FromString("Count not add {0} to the Inventory. No remaining inventory slots, or invalid item."), 
			InputItem->GetTextData().Name));
		}
	}

	//Owner가 없을 때 프로젝트를 다운시킨다.
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed"));
	
}


void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd)
{
	UItemBase* NewItem;

	// 땅에 떨어져 있을 경우와 이미 인	벤토리 메모리 상에 같은 데이터가 존재할 경우는 ItemCopy를 시키지 않는다. 
	if(Item->bIsCopy || Item->bIsPickup)
	{
		// 기존에 있던 항목의 플래그들만 변경한다.
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		// 다른 인벤토리 또는 처음 만들어진 데이터를 카피한다.
		NewItem = Item->CreateItemCopy();
	}

	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	InventoryContents.Add(NewItem);
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	OnInventoryUpdated.Broadcast();
}

