
//game
#include "Characters/Components/InventoryComponent.h"
#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryPannel.h"

//engine
#include "Algo/Sort.h"

constexpr int NONFIND_INDEX = -1;

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

const int32 UInventoryComponent::FindEmptyItemIndex(int32 FirstIndex) const
{
	// 아이템이 배열안에 존재하면 반환한다.
	for(int32 i = FirstIndex; i < InventoryContents.Num(); ++i)
	{
		if(!InventoryContents[i])
			return i;
	}

	return NONFIND_INDEX;
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
	// 순회하면서 만약 ID가 같거나 스택이 다 채워져있지 않다면 결과를 반환한다.
	// 이 때 ItemIn의 스택이 너무 크다면 여러 번 받아야 하기 때문에 반복문을 수행하자. -> 호출하는 함수에서 실행
	if(ItemIn)
	{
		for (int i = 0; i < InventoryContents.Num(); ++i)
		{
			if (!InventoryContents[i])
				continue;

			if(InventoryContents[i]->ID == ItemIn->ID && !InventoryContents[i]->IsFullItemStack())
				return InventoryContents[i];
		}
	}

	return nullptr;
}

int32 UInventoryComponent::CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	// (인벤토리 무게 - 인벤토리 들고 있는 현재 무게) / 아이템의 무게
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->NumericData.Weight);

	// 아이템을 다 넣을 수 있다고 판단된다.
	if(WeightMaxAddAmount >= RequestedAddAmount)
	{
		return RequestedAddAmount;
	}

	// 아이템을 다 넣을 수 없으니 무게만큼만 넣을 수 있도록 반환하자.
	return WeightMaxAddAmount;
}

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount)
{

	int StackSize = StackableItem->NumericData.MaxStackSize;

	// 인벤토리 안에 들어가있는 (아이템 최대 수량 - 현재 수량) 
	const int32 AddAmountToMakeFullStack = FMath::Max(StackSize, StackSize - StackableItem->Quantity);

	// min(내가 넣고 싶은 아이템의 수량, 인벤토리에 최대로 들어갈 수 있는 수량)
	//
	// ex)	내가 아이템을 10개를 넣어야 하는데 인벤토리 이 아이템은 3개 밖에 못넣는다. 그러면 3개 반환
	//		똑같이 10개를 넣어야 하는데 이 아이템은 100개 이하는 넣을 수 있고 10개가 차있다. 그러면 10개 반환

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	// 아이템과 같은 주소를 가지고 있다면 그 아이템을 지우고 업데이트 시켜주자.

	for (int i = 0; i < InventoryContents.Num(); ++i)
	{
		if (InventoryContents[i] == ItemToRemove)
		{
			InventoryContents[i] = nullptr;
			return;
		}
	}

	//InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
	// min(삭제할 만큼의 아이템 수량, 현재 내가 가지고 있는 아이템 수량)
	// 하는 이유 -> 아이템 분할(스플릿) 하기 때문이다. 
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, ItemIn->Quantity);

	// 삭제할 양 만큼 아이템의 수량을 맞춰준다.
	ItemIn->SetQuantity(ItemIn->Quantity - ActualAmountToRemove);

	// 삭제할 양 만큼 인벤토리의 무게를 맞춰준다.
	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();

	OnInventoryUpdated.Broadcast();

	// 삭제할 양을 반환한다.
	return ActualAmountToRemove;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	const int index = FindEmptyItemIndex(0);

	if(index != NONFIND_INDEX)
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit, index);
	}
}

void UInventoryComponent::SwapInventory(UInventoryItemSlot* Sour, UInventoryItemSlot* Dest)
{
	const int32 SourIndex = Sour->GetSlotIndex();
	const int32 DestIndex = Dest->GetSlotIndex();

	// 인벤토리에 들어있는 Index 기준으로 데이터만을 Swap 한다.
	UItemBase* tmp = InventoryContents[DestIndex];
	InventoryContents[DestIndex] = InventoryContents[SourIndex];
	InventoryContents[SourIndex] = tmp;

}

FItemAddResult UInventoryComponent::HandelNonStackableItems(UItemBase* InputItem)
{
	// 수량 * 아이템 무게
	const float StackWeigt = InputItem->GetItemStackWeight();

	// 들어가는 아이템의 무게가 있는 지 체크1
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

	// 인벤토리 빈 곳의 Index를 찾는다.
	const int32 FindItemIdx = FindEmptyItemIndex(0);

	// 만약 인벤토리가 다 찼다면 추가하지 않는다.
	if(FindItemIdx == NONFIND_INDEX)
	{
		return FItemAddResult::AddedNone(FText::Format
		(FText::FromString("Count not add {0} to the Inventory. All invetory slots are full."), InputItem->GetTextData().Name));
	}

	// 인벤토리 빈 곳의 아이템을 넣어준다.
	AddNewItem(InputItem, 1, FindItemIdx);
	OnInventoryUpdated.Broadcast();

	// 슬롯에 모든 아이템을 담았기 때문에 Instance을 Destory() 시킨다.
	return FItemAddResult::AddedAll(1, FText::Format
	(FText::FromString("Successfully added a single {0} to the Inventory."), InputItem->GetTextData().Name));
}

int32 UInventoryComponent::HandelStackableItems(UItemBase* ItemIn, int32 RequestedAddAmount)
{
	// 추가할 아이템의 개수가 0이거나 weight 가 0이라면 return 0;
	if(RequestedAddAmount <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		return 0;
	}

	// 필요한 아이템 수량(반복문에서 사용)
	int32 AmountToDistribute = RequestedAddAmount;

	// 이미 인벤토리에 있는 지 확인하고 없으면 새로 인벤토리에 추가해 넣는다.
	UItemBase* ExistingItemStack = FindNextPartialStack(ItemIn);

	// 아이템 데이터가 없는 곳에 아이템 데이터를 넣어주자.
	int32 FindItemIdx = FindEmptyItemIndex();

	if (!ExistingItemStack)
	{
		if(FindItemIdx == NONFIND_INDEX)
			return 0;

		ExistingItemStack = ItemIn;
	}
		

	// 인벤토리가 수용할 수 있을 정도로 다 찰 때 까지 루프를 돌리자.
	while (AmountToDistribute)
	{
		// 아이템의 전체 수량을 반환한다.(기준 min(아이템 최대 개수, 필요한 아이템의개수))
		const int32 AmountToMakeFullstack = CalculateNumberForFullStack( ExistingItemStack , AmountToDistribute );
		// 아이템의 무게를 기반해서 아이템을 얼마 넣을 수 있는 지 확인한다.	
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount( ExistingItemStack , AmountToMakeFullstack );

		// 수량이 남아 있다면?(무게가 존재한다면?)
		if (WeightLimitAddAmount > 0)
		{
			// 무게를 기반한 아이템이 만약 현재 필요량보다 작다면
			// 몇 개 못넣는다..
			if (WeightLimitAddAmount > AmountToDistribute)
			{
				// 다 넣지 못한 수량만큼 아이템의 수량을 업데이트(감소) 시켜주자.
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetQuantity( AmountToDistribute );

				// 필요한 양의 아이템을 모두 못 넣기 때문에 데이터를 카피해서 넣어주자.
				AddNewItem( ItemIn->CreateItemCopy() , WeightLimitAddAmount , FindItemIdx );
				return RequestedAddAmount - AmountToDistribute;
			}

			//// 기존 수량에서 추가한다.
			//ExistingItemStack->SetQuantity( ExistingItemStack->Quantity + WeightLimitAddAmount );

			// 기존 무게에서 들어노는 무게와 기존 무게를 더해준다.
			//InventoryTotalWeight += ExistingItemStack->GetItemSingleWeight() * WeightLimitAddAmount;

			// 현재 필요한 아이템 수량 -= 실제로 운반할 수 있는 아이템 수량
			AmountToDistribute -= WeightLimitAddAmount;

			// 내가 옮긴 아이템 남은 수량으로 바꿔준다.
			ItemIn->SetQuantity( AmountToDistribute );

			// 만약 최대 무게에 도달하면 루프를 실행할 필요가 없기 때문에 반환한다.
			if (InventoryTotalWeight >= InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}

			AddNewItem(ItemIn, WeightLimitAddAmount , FindItemIdx);

		}
		else if (WeightLimitAddAmount <= 0)
		{
			// 아이템 무게가 존재하지 않고, 아이템 필요 추가량 != 현재 필요한 아이템 수량 이라면
			if (AmountToDistribute != RequestedAddAmount)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}

			return 0;
		}

		// 아이템을 인벤토리에 다 넣었을 경우 들어온다.
		if (AmountToDistribute <= 0)
		{
			OnInventoryUpdated.Broadcast();
			return RequestedAddAmount;
		}

		// 아이템이 남아있는 지 체크한다.
		ExistingItemStack = FindNextItemByID( ItemIn );
		FindItemIdx = FindEmptyItemIndex( ++FindItemIdx );

		if (!ExistingItemStack)
		{
			if (FindItemIdx == NONFIND_INDEX)
				return RequestedAddAmount - AmountToDistribute;

			ExistingItemStack = ItemIn;
		}
	}

	// partial stack을 찾을 수 없을 때 새로운 스택에 추가한다.
	//if(InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	//{
	//	// 아이템의 무게를 기반해서 아이템을 얼마 넣을 수 있는 지 확인한다.
	//	const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ItemIn, AmountToDistribute);

	//	

	//	// 아이템 무게가 존재한다면?
	//	if(WeightLimitAddAmount >= 0)
	//	{

	//		// 무게를 비교해서 현재 필요량보다 크다면 모두 넣어주자.
	//
	//		return RequestedAddAmount;
	//	}
	//}

	OnInventoryUpdated.Broadcast();
	return RequestedAddAmount - AmountToDistribute;
}

FItemAddResult UInventoryComponent::HandelAddItem(UItemBase* InputItem)
{
	if(GetOwner())
	{
		// 아이템의 수량
		const int32 InitialRequestedAddAmount = InputItem->Quantity;

		// 스택에 쌓이지 않는 아이템 반환 ex) 무기, 방어구 등
		if(!InputItem->NumericData.bIsStackable)
		{
			// 아이템을 담을 수 있는 지 체크하고 반환한다.
			return HandelNonStackableItems(InputItem);
		}

		// 스택에 쌓이는 아이템 반환 ex) 소비 아이템 등
		const int32 StackableAmountAdded = HandelStackableItems(InputItem, InitialRequestedAddAmount);

		// 인벤토리에 담을 수 있는 양 == 인벤토리에 담아야 하는 양
		if(StackableAmountAdded == InitialRequestedAddAmount)
		{
			// 모두 인벤토리에 넣어주자.
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Successfully added {0} {1} to the Inventory."), 
			InitialRequestedAddAmount, InputItem->GetTextData().Name));
			
		}

		// 인벤토리에 담을 수 있는 양 < 인벤토리에 담아야 하는 양
		// 인벤토리에 담을 수 있는 양 > 0 -> 인벤토리가 비어 있는 지 확인.
		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			// 부분만 인벤토리에 넣어주자.
			return FItemAddResult::AddedPartial(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Partial amount of {0} added to thie Inventory. Number added {1}"), 
			InputItem->GetTextData().Name, InitialRequestedAddAmount));
		}

		// 인벤토리가 꽉 차있다면
		if(StackableAmountAdded <= 0)
		{
			// 인벤토리에 넣지 못한다.
			return FItemAddResult::AddedNone(FText::Format
			(FText::FromString("Count not add {0} to the Inventory. No remaining inventory slots, or invalid item."), 
			InputItem->GetTextData().Name));
		}
	}

	//Owner가 없을 때 프로젝트를 다운시킨다.
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryAddItem fallthrough error. GetOwner() check somehow failed"));
}



void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd, const int32 InputItemIndex)
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

	// InventoryComponent 를 동기화시켜주고, 아이템 수량을 넣어준다.
	NewItem->OwningInventory = this;
	NewItem->SetQuantity(AmountToAdd);

	// 인벤토리에 아이템 데이터를 아이템 데이터가 없는 인덱스에 추가한다.
	InventoryContents[InputItemIndex] = NewItem;

	// PlayerMainHUD를 가져오자.
	if(const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
	{
		// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
		if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
			InventoryPanel->RefreshInventoryPannel( InputItemIndex , NewItem );
	}

	// 인벤토리의 무게를 늘려주자.
	InventoryTotalWeight += NewItem->GetItemStackWeight();
	//OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::SortItem_Name()
{
	Algo::Sort( InventoryContents , []( const UItemBase* A, const UItemBase* B ) 
	{
		// A가 nullptr이면 B가 앞으로 가야 하므로 false 반환
		if (!A) return false;
		// B가 nullptr이면 A가 앞으로 가야 하므로 true 반환
		if (!B) return true;

		return A->GetTextData().Name.ToString() < B->GetTextData().Name.ToString();
	});

	// PlayerMainHUD를 가져오자.
	if (const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
	{
		// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
		if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
		{
			//for(int i = 0; i < InventorySlotsCapacity)
			for (int i = 0; i < 100; ++i) // test
			{
				InventoryPanel->RefreshInventoryPannel( i , InventoryContents[i] );
			}

		}
	}
}
