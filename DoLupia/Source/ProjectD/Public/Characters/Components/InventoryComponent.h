// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemBase.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

class UItemBase; class UInventoryItemSlot; class UItemPool; class UItemWidgetPool; class UItemCarouselWidget;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item added"),
	IAR_PartialAmoutItemAdded UMETA(DisplayName = "Partial amount of Item added"),
	IAR_AllItemAdded UMETA(DisplayName = "All of item added")
};

UENUM( BlueprintType )
enum class ESortType : uint8
{
	Sort_Name,
	Sort_Type,
	Sort_Grade
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_USTRUCT_BODY()

	FItemAddResult() :
	ActualAmountAdded(0),
	OperationResult(EItemAddResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty())
	{};


	// 인벤토리에 추가된 실제 품목 금액
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;
	// 항목 추가 작업의 종료 상태를 나타내는 열거형
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;
	// 결과와 함께 전달될 수 있는 정보 메시지
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;

		return AddedNoneResult;
	};
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = PartialAmountAdded;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_PartialAmoutItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;

		return AddedNoneResult;
	};

	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = AmountAdded;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedNoneResult.ResultMessage = Message;

		return AddedNoneResult;
	};
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void SortItem_Name();

	FItemAddResult HandelAddItem(UItemBase* InputItem, bool bResetFlag = false);

	void HandelRemoveItem(const TMap<FString , int32>& RemoveToITem);
	void HandelRemoveItem(FString ItemName, int32 ItemCount = 1, bool QuickSlotUseItem = false);

	void ReleaseInventory(UItemBase* ItemIn);

	const int32 FindEmptyItemIndex(int32 FirstIndex = 0, const FString& InKey = "") const;

	UItemBase* FindMatchItem(UItemBase* ItemIn) const;
	UItemBase* FindMatchItem( const FString& ItemID ) const;
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;
	UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;
	int32 FindItemQuantity(const FString& InKey);

	void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove, bool IsRemoveItem );
	int32 RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove);
	void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);

	void SwapInventory(UInventoryItemSlot* Sour, UInventoryItemSlot* Dest);

	// getters
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };
	FORCEINLINE int32 GetSlotCapacity() const { return InventorySlotsCapacity; };
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; };
	int32 GetInventoryItemCount(const FString& InKey);

	// setters
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotCapacity) { InventorySlotsCapacity = NewSlotCapacity; };
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity;};
	FORCEINLINE void AddInventoryContents(UItemBase* AddNewItem) { InventoryContents.Add( AddNewItem ); };

	// 인벤토리 업데이트 델리게이트
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	virtual void BeginPlay() override;

	FItemAddResult HandelNonStackableItems(UItemBase* InputItem);
	int32 HandelStackableItems(UItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount, bool IsFindStackItem );

	void AddNewItem(UItemBase* Item, const int32 AmountToAdd, const int32 InputItemIndex);
	void DeleteItem(const FString& ItemName, const int32 AmountToAdd, const int32 SearchInventoryIndex = 0, bool QuickSlotItemDelete = false );

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;

	UPROPERTY(VisibleAnywhere, Category = "Inventory" )
	TMap<FString, int32> InventoryCount;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UItemPool> ItemPool;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItemWidgetPool> ItemWidgetPool;

	UPROPERTY()
	TObjectPtr<UItemCarouselWidget> ItemCarouselWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemCarouselWidget> LootingItemWidgetFactory;


	FTimerHandle ItemCarouselWidgetIHandle;

	//퀘스트에 보내기 위해
	UPROPERTY()
	class AProjectDCharacter* player;
};
