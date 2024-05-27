
//game
#include "Characters/Components/InventoryComponent.h"
#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Inventory/InventoryItemSlot.h"
#include "UserInterface/Inventory/InventoryPannel.h"
#include "Pooling/ItemPool.h"

//engine
#include "Algo/Sort.h"
#include "Characters/PlayerStat.h"
#include "Characters/ProjectDCharacter.h"
#include "UserInterface/Item/ItemCarouselWidget.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"


constexpr int32 NONFIND_INDEX = -1;


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // 나중에 삭제

	ItemPool = CreateDefaultSubobject<UItemPool>(TEXT("ItemPool"));
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AProjectDCharacter>( GetOwner() );

	//InventorySlotsCapacity
	ItemPool->CreateItem(100);

	ItemCarouselWidget = CreateWidget<UItemCarouselWidget>(GetWorld(), LootingItemWidgetFactory);
	ItemCarouselWidget->AddToViewport();
}

//

void UInventoryComponent::ReleaseInventory(UItemBase* ItemIn)
{
	if(!ItemIn)
		return;

	// 아이템이 배열안에 존재하면 반환한다.
	for (int32 i = 0; i < InventoryContents.Num(); ++i)
	{
		if (!InventoryContents[i])
			continue;

		if (InventoryContents[i] == ItemIn)
		{
			ItemPool->ReturnItem(InventoryContents[i]);
			InventoryContents[i] = nullptr;

			const FString& InKey = ItemIn->GetTextData().Name.ToString();
			const int32* ElemValue = InventoryCount.Find(InKey);
			const int32 Quantity = ItemIn->GetQuantity();

			if(!ElemValue)
				InventoryCount.Remove( InKey );

			UE_LOG(LogTemp, Warning, TEXT("ReleaseInventory Sucesssed"));
			break;
		}
	}
}

const int32 UInventoryComponent::FindEmptyItemIndex(int32 FirstIndex, const FString& InKey) const
{
	// 인벤토리 안에 있는 아이템을 찾고
	// 만약 없다면 빈 곳에
	// 있다면 수량이 들어갈 수 있는 곳에 넣어주자.
	int32 Index = NONFIND_INDEX;
	const int32* ElemValue = InventoryCount.Find(InKey);

	// 아이템이 배열안에 존재하면 반환한다.
	for(int32 i = FirstIndex; i < InventoryContents.Num(); ++i)
	{
		if(!ElemValue)
		{
			if (!InventoryContents[i])
				return i;
		}
		else
		{
			if (!InventoryContents[i])
			{
				if(Index == NONFIND_INDEX)
					Index = i;

				continue;
			}

			if(InKey == InventoryContents[i]->GetTextData().Name.ToString() && !InventoryContents[i]->IsFullItemStack())
				return i;

		}
	}

	return Index;
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

UItemBase* UInventoryComponent::FindMatchItem(const FString& ItemID) const
{

	for(UItemBase* Item : InventoryContents)
	{
		if(Item)
			if(Item->ID == ItemID)
				return Item;
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
		for (int32 i = 0; i < InventoryContents.Num(); ++i)
		{
			if (!InventoryContents[i])
				continue;

			if(InventoryContents[i]->ID == ItemIn->ID && !InventoryContents[i]->IsFullItemStack())
				return InventoryContents[i];
		}
	}

	return nullptr;
}

int32 UInventoryComponent::FindItemQuantity(const FString& InKey)
{
	const int32* ElemValue = InventoryCount.Find( InKey );

	int32 Result = 0;

	if (ElemValue)
		Result = *ElemValue;

	return Result;
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

int32 UInventoryComponent::CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount, bool IsFindStackItem)
{

	const int32 StackSize = StackableItem->NumericData.MaxStackSize;
	int32 AddNum = StackSize - StackableItem->Quantity;

	if(AddNum <= 0)
	{
		if(StackSize <= StackableItem->Quantity)
			AddNum = StackSize;
	}
	else
	{
		if(!IsFindStackItem)
			AddNum = StackableItem->Quantity;
	}
	//else
	//	AddNum = FMath::Max(AddNum, StackableItem->Quantity );

		

	// 인벤토리 안에 들어가있는 (아이템 최대 수량 - 현재 수량) 
	const int32 AddAmountToMakeFullStack = FMath::Min(StackSize, AddNum);

	// min(내가 넣고 싶은 아이템의 수량, 인벤토리에 최대로 들어갈 수 있는 수량)
	//
	// ex)	내가 아이템을 10개를 넣어야 하는데 인벤토리 이 아이템은 3개 밖에 못넣는다. 그러면 3개 반환
	//		똑같이 10개를 넣어야 하는데 이 아이템은 100개 이하는 넣을 수 있고 10개가 차있다. 그러면 10개 반환

	return FMath::Min(InitialRequestedAddAmount, AddAmountToMakeFullStack);
}

void UInventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove, bool IsRemoveItem )
{
	// 아이템과 같은 주소를 가지고 있다면 그 아이템을 지우고 업데이트 시켜주자.

	for (int32 i = 0; i < InventoryContents.Num(); ++i)
	{
		if (InventoryContents[i] == ItemToRemove)
		{
			const FString& InKey = ItemToRemove->GetTextData().Name.ToString();
		
			if(InventoryCount.Contains(InKey))
			{
				int32& Quantity = InventoryCount[InKey];
				Quantity -= ItemToRemove->GetQuantity();

				if(Quantity <= 0)
				{
					InventoryCount.Remove(InKey);
				}
					
			}

			if(IsRemoveItem)
			{
				ItemPool->ReturnItem( InventoryContents[i] );
				InventoryContents[i] = nullptr;
			}

			return;
		}
	}

	OnInventoryUpdated.Broadcast();
}

int32 UInventoryComponent::RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{

	const int32 Quantity = ItemIn->NumericData.bIsStackable ? ItemIn->Quantity : 1;

	// min(삭제할 만큼의 아이템 수량, 현재 내가 가지고 있는 아이템 수량)
	// 하는 이유 -> 아이템 분할(스플릿) 하기 때문이다. 
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmountToRemove, Quantity);

	// 삭제할 양 만큼 아이템의 수량을 맞춰준다.
	ItemIn->SetQuantity(Quantity - ActualAmountToRemove, true);

	// 삭제할 양 만큼 인벤토리의 무게를 맞춰준다.
	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetItemSingleWeight();
	InventoryCount[ItemIn->GetTextData().Name.ToString()] -= DesiredAmountToRemove;

	OnInventoryUpdated.Broadcast();

	// 삭제할 양을 반환한다.
	return ActualAmountToRemove;
}

void UInventoryComponent::SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit)
{
	const int32 index = FindEmptyItemIndex();

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

int32 UInventoryComponent::GetInventoryItemCount(const FString& InKey)
{
	const int32* ElemPtr = InventoryCount.Find(InKey);

	if(ElemPtr)
		return *ElemPtr;

	return 0;
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
	const int32 FindItemIdx = FindEmptyItemIndex();

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
	bool IsFindStack = ExistingItemStack ? true : false;

	// 현재 내가 넣고 싶은 아이템이름을 가져오자.
	FString ItemName = ItemIn->GetTextData().Name.ToString();

	// 아이템 데이터가 없는 곳에 아이템 데이터를 넣어주자.
	int32 FindItemIdx = FindEmptyItemIndex(0, ItemName);


	if (!ExistingItemStack)
	{
		if(FindItemIdx == NONFIND_INDEX)
			return 0;

		ExistingItemStack = ItemIn;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ExistingItemStack : is not null!"));
	}
		

	// 인벤토리가 수용할 수 있을 정도로 다 찰 때 까지 루프를 돌리자.
	while (AmountToDistribute)
	{
		// 아이템의 전체 수량을 반환한다.(기준 min(아이템 최대 개수, 필요한 아이템의개수))
		const int32 AmountToMakeFullstack = CalculateNumberForFullStack( ExistingItemStack , AmountToDistribute, IsFindStack );
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
				ItemIn->SetQuantity( AmountToDistribute, false );

				// 필요한 양의 아이템을 모두 못 넣기 때문에 데이터를 카피해서 넣어주자.
				AddNewItem(ExistingItemStack , WeightLimitAddAmount , FindItemIdx );
				return RequestedAddAmount - AmountToDistribute;
			}

			// 현재 필요한 아이템 수량 -= 실제로 운반할 수 있는 아이템 수량
			AmountToDistribute -= WeightLimitAddAmount;

			// 내가 옮긴 아이템 남은 수량으로 바꿔준다.
			ItemIn->SetQuantity( AmountToDistribute, false );

			// 만약 최대 무게에 도달하면 루프를 실행할 필요가 없기 때문에 반환한다.
			if (InventoryTotalWeight >= InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();
				return RequestedAddAmount - AmountToDistribute;
			}

			AddNewItem(ExistingItemStack, WeightLimitAddAmount , FindItemIdx);

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

		IsFindStack ? FindItemIdx = FindEmptyItemIndex( 0 , ItemName ) : FindItemIdx = FindEmptyItemIndex( ++FindItemIdx , ItemName );
		IsFindStack = ExistingItemStack ? true : false;

		if (!ExistingItemStack)
		{
			if (FindItemIdx == NONFIND_INDEX)
				return RequestedAddAmount - AmountToDistribute;

			ExistingItemStack = ItemIn;
		}
	}

	OnInventoryUpdated.Broadcast();
	return RequestedAddAmount - AmountToDistribute;
}

FItemAddResult UInventoryComponent::HandelAddItem(UItemBase* InputItem)
{
	if(GetOwner())
	{
		// 아이템의 수량
		int32 InitialRequestedAddAmount = InputItem->Quantity;

		// 스택에 쌓이지 않는 아이템 반환 ex) 무기, 방어구 등
		if(!InputItem->NumericData.bIsStackable)
		{
			// 아이템을 담을 수 있는 지 체크하고 반환한다.
			FItemAddResult Result = HandelNonStackableItems( InputItem );

			switch (Result.OperationResult)
			{

			case EItemAddResult::IAR_PartialAmoutItemAdded:
				ItemCarouselWidget->AddItemWidget( InputItem->GetTextData().Name , InitialRequestedAddAmount - InputItem->Quantity , InputItem->GetAssetData().Icon );
				player->OnObjectiveIDCalled.Broadcast( InputItem->GetTextData().Name.ToString() , InputItem->Quantity );

				break;
			case EItemAddResult::IAR_AllItemAdded:
				ItemCarouselWidget->AddItemWidget( InputItem->GetTextData().Name, InitialRequestedAddAmount, InputItem->GetAssetData().Icon );
				player->OnObjectiveIDCalled.Broadcast( InputItem->GetTextData().Name.ToString() , InputItem->Quantity );

				break;
			default: ;
			}

			return Result;
		}

		// 스택에 쌓이는 아이템 반환 ex) 소비 아이템 등
		const int32 StackableAmountAdded = HandelStackableItems(InputItem, InitialRequestedAddAmount);

		// 인벤토리에 담을 수 있는 양 == 인벤토리에 담아야 하는 양
		if(StackableAmountAdded == InitialRequestedAddAmount)
		{
			ItemCarouselWidget->AddItemWidget( InputItem->GetTextData().Name , InitialRequestedAddAmount , InputItem->GetAssetData().Icon );
			const FString& ItemName = InputItem->GetTextData().Name.ToString();
			player->OnObjectiveIDCalled.Broadcast( ItemName , InitialRequestedAddAmount );

			player->GetPlayerDefaultsWidget()->RefreshQuickSlot( ItemName , InventoryCount[ItemName] );

			// 모두 인벤토리에 넣어주자.
			return FItemAddResult::AddedAll(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Successfully added {0} {1} to the Inventory."), 
			InitialRequestedAddAmount, InputItem->GetTextData().Name));
			
		}

		// 인벤토리에 담을 수 있는 양 < 인벤토리에 담아야 하는 양
		// 인벤토리에 담을 수 있는 양 > 0 -> 인벤토리가 비어 있는 지 확인.
		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			int AddedAmount = InitialRequestedAddAmount - StackableAmountAdded;
			ItemCarouselWidget->AddItemWidget( InputItem->GetTextData().Name , AddedAmount , InputItem->GetAssetData().Icon );

			const FString& ItemName = InputItem->GetTextData().Name.ToString();
			player->OnObjectiveIDCalled.Broadcast( ItemName , AddedAmount );

			player->GetPlayerDefaultsWidget()->RefreshQuickSlot( ItemName , InventoryCount[ItemName]);

			// 부분만 인벤토리에 넣어주자.
			return FItemAddResult::AddedPartial(InitialRequestedAddAmount, FText::Format
			(FText::FromString("Partial amount of {0} added to thie Inventory. Number added {1}"), 
			InputItem->GetTextData().Name, AddedAmount ));
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

void UInventoryComponent::HandelRemoveItem(const TMap<FString, int32>& RemoveToITem )
{

	TArray<TPair<FString, int32>> ItemName;

	for(const auto& Iterate : RemoveToITem)
	{
		const int32* Value = InventoryCount.Find( Iterate.Key );

		if(!Value || *Value < Iterate.Value)
		{
			UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent::HandelRemoveItem() -> Not Enough Item Quantity"));
			return;
		}

		ItemName.Add( { Iterate.Key, Iterate.Value } );
	}

	if (GetOwner())
	{
		int32 Index = 0;
		for(TPair<FString , int32> Items : ItemName)
		{
			DeleteItem( Items.Key , Items.Value, Index );

			const int32* ElemValue = InventoryCount.Find(Items.Key);
			if(ElemValue)
			{
				player->GetPlayerDefaultsWidget()->RefreshQuickSlot( Items.Key , InventoryCount[Items.Key] );
			}
		}

		OnInventoryUpdated.Broadcast();
	}
}

void UInventoryComponent::HandelRemoveItem(FString ItemName, int32 ItemCount, bool QuickSlotUseItem)
{
	if (GetOwner())
	{
		DeleteItem( ItemName , ItemCount, 0, QuickSlotUseItem);

		const int32* ElemValue = InventoryCount.Find( ItemName );
		if (ElemValue)
		{
			player->GetPlayerDefaultsWidget()->RefreshQuickSlot( ItemName , InventoryCount[ItemName] );
			UE_LOG(LogTemp, Warning, TEXT("%d"), player->GetPlayerStat()->GetHP() )
		}
		else
			player->GetPlayerDefaultsWidget()->RefreshQuickSlot( ItemName , 0 );

		OnInventoryUpdated.Broadcast();
	}
}


void UInventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountToAdd, const int32 InputItemIndex)
{
	UItemBase* NewItem;

	const int32 ItemSourQuantity = Item->GetQuantity();

	// 땅에 떨어져 있을 경우와 이미 인	벤토리 메모리 상에 같은 데이터가 존재할 경우는 ItemCopy를 시키지 않는다. 
	if(Item->bIsCopy || Item->bIsPickup)
	{
		// 기존에 있던 항목의 플래그들만 변경한다.
		NewItem = Item;

		// 만약 아이템이 현재 칸에 다 찰 수 있다면 flag 값을 false 로 바꿔주자.
		if(AmountToAdd + ItemSourQuantity == Item->GetNumericData().MaxStackSize)
			NewItem->ResetItemFlags();
	}
	else
	{
		// 다른 인벤토리 또는 처음 만들어진 데이터를 카피한다.
		NewItem = ItemPool->GetItem(Item->GetTextData().Name.ToString()); //Item->CreateItemCopy();
	}

	// 인벤토리의 무게를 늘려주자.
	InventoryTotalWeight += NewItem->GetItemSingleWeight() * AmountToAdd;



	// InventoryComponent 를 동기화시켜주고, 아이템 수량을 넣어준다.
	NewItem->OwningInventory = this;

	const int32 MaxStackSize = NewItem->GetNumericData().MaxStackSize;
	const int32 AddQuantity = AmountToAdd + ItemSourQuantity;

	if(AddQuantity > MaxStackSize)
		NewItem->SetQuantity( MaxStackSize, false );
	else
		NewItem->SetQuantity( AddQuantity, false );
	

	// 인벤토리에 아이템 데이터를 아이템 데이터가 없는 인덱스에 추가한다.
	InventoryContents[InputItemIndex] = NewItem;


	FString ItemName = Item->GetTextData().Name.ToString();
	const int32* ElemPtr = InventoryCount.Find( ItemName );

	if (ElemPtr)
		InventoryCount[ItemName] += AmountToAdd;
	else
	{
		InventoryCount.Emplace( ItemName , AmountToAdd );
	}


	// PlayerMainHUD를 가져오자.
	if(const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
	{
		// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
		if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
			InventoryPanel->RefreshInventoryPannel( InputItemIndex , NewItem );
	}
	
	//OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::DeleteItem(const FString& ItemName, const int32 AmountToAdd, const int32 SearchInventoryIndex, bool QuickSlotItemDelete)
{
	int32 Index = SearchInventoryIndex;
	int32 ToAdd = AmountToAdd;

	while(ToAdd)
	{
		UItemBase* ExistingItemStack = nullptr;

		for (; Index < InventoryContents.Num(); ++Index)
		{
			if (!InventoryContents[Index])
				continue;

			if (InventoryContents[Index]->TextData.Name.ToString() == ItemName)
			{
				ExistingItemStack = InventoryContents[Index];
				break;
			}
		}

		if(!ExistingItemStack)
			break;



		const int32 Quantity = (!QuickSlotItemDelete && ExistingItemStack->GetNumericData().bIsStackable) ? ExistingItemStack->GetQuantity() : 1;

		// 인벤토리의 무게를 줄여주자.
		InventoryTotalWeight -= ExistingItemStack->GetItemSingleWeight() * Quantity;

		QuickSlotItemDelete
			? ExistingItemStack->SetQuantity( ExistingItemStack->GetQuantity() - 1, false )
			: ExistingItemStack->SetQuantity( FMath::Min( 0 , ExistingItemStack->GetQuantity() - ToAdd ), false);

		if (int32* ElemPtr = InventoryCount.Find( ItemName ))
		{
			*ElemPtr -= Quantity;

			if (*ElemPtr == 0)
				InventoryCount.Remove( ItemName );
		}

		ToAdd -= Quantity;
		
		// 만약 아이템 슬롯에 있는 아이템을 다 비웠으면
		if (ExistingItemStack->GetQuantity() <= 0)
		{
			ItemPool->ReturnItem(ExistingItemStack);

			// InventoryComponent를 비워주자.
			ExistingItemStack->OwningInventory = nullptr;
			// 인벤토리에 아이템 수량이 0인 인벤토리의 인덱스를 비워주자.
			InventoryContents[Index] = nullptr;

			// PlayerMainHUD를 가져오자.
			if (const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
			{
				// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
				if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
					InventoryPanel->RefreshInventoryPannel( Index , nullptr );
			}
		}
		else
		{
			// PlayerMainHUD를 가져오자.
			if (const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
			{
				// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
				if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
					InventoryPanel->RefreshInventoryPannel( Index , ExistingItemStack );
			}
		}
	}

}

void UInventoryComponent::SortItem_Name()
{

	/*TArray<TTuple<FString , TObjectPtr<UItemBase>, int32>> Pairs;

	for (auto Elem : InventoryItembaseStorage)
	{
		Pairs.Push({Elem.Key, Elem.Value, InventoryCount[Elem.Key]});
	}*/

	for(int32 i = 0; i < 100; ++i)
	{
		if(InventoryContents[i])
		{
			ItemPool->ReturnItem(InventoryContents[i]);
			InventoryContents[i] = nullptr;
		}
		
	}

	InventoryTotalWeight = 0.0f;

	//Algo::Sort( Pairs, [](	const TTuple<FString , TObjectPtr<UItemBase> , int32>& A, 
	//						const TTuple<FString , TObjectPtr<UItemBase> , int32>& B)
	//{
	//	const FString SourName = A.Get<0>();
	//	const FString DestName = B.Get<0>();

	//	return SourName < DestName;
	//});

		// TArray에 TMap의 내용을 (키, 값) 쌍으로 복사
	TArray<TPair<FString , int32>> PP;
	for (const TPair<FString , int32>& Pair : InventoryCount)
	{
		PP.Add( Pair );
	}

	// TArray 정렬, 람다식을 사용하여 키 기준으로 정렬
	PP.Sort( []( const TPair<FString , int32>& A , const TPair<FString , int32>& B ) {
		return A.Key < B.Key; // 오름차순 정렬
	} );

	for(auto Iterate : PP)
	{
		TObjectPtr<UItemBase> CopyItemBase = ItemPool->GetItem(Iterate.Key);

		if (CopyItemBase->GetNumericData().bIsStackable && CopyItemBase->GetNumericData().MaxStackSize)
		{
			while (Iterate.Value)
			{
				const int32 AddNum = FMath::Min( Iterate.Value , CopyItemBase->GetNumericData().MaxStackSize );
				Iterate.Value -= AddNum;
				CopyItemBase->SetQuantity( AddNum , false);
				HandelStackableItems( CopyItemBase , AddNum );
				CopyItemBase->ResetItemFlags();
				CopyItemBase = ItemPool->GetItem( Iterate.Key );
			}
		}
		else
		{
			while (Iterate.Value--)
			{
				CopyItemBase->SetQuantity( 1, false );
				HandelNonStackableItems( CopyItemBase );
				CopyItemBase->ResetItemFlags();
				CopyItemBase = ItemPool->GetItem( Iterate.Key );
			}

		}

		ItemPool->ReturnItem(CopyItemBase);

		InventoryCount[Iterate.Key] /= 2;
	}

	// PlayerMainHUD를 가져오자.
	if (const ADoLupiaHUD* HUD = Cast<ADoLupiaHUD>( GetWorld()->GetFirstPlayerController()->GetHUD() ))
	{
		// HUD에 InventoryPanel를 가져와서 Inventory Widget을 업데이트 시켜주자.
		if (UInventoryPannel* InventoryPanel = HUD->GetMainMeun()->GetInventoryPanel())
		{
			//for(int i = 0; i < InventorySlotsCapacity)
			for (int32 i = 0; i < 100; ++i) // test
			{
				InventoryPanel->RefreshInventoryPannel( i , InventoryContents[i] );
			}

		}
	}
}
