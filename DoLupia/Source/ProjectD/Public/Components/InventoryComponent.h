// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ItemBase.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);

class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item added"),
	IAR_PartialAmoutItemAdded UMETA(DisplayName = "Partial amount of Item added"),
	IAR_AllItemAdded UMETA(DisplayName = "All of item added")
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


	// �κ��丮�� �߰��� ���� ǰ�� �ݾ�
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;
	// �׸� �߰� �۾��� ���� ���¸� ��Ÿ���� ������
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;
	// ����� �Բ� ���޵� �� �ִ� ���� �޽���
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

	UFUNCTION(Category = "Inventory")
	FItemAddResult HandelAddItem(UItemBase* InputItem);

	UFUNCTION(Category = "Inventory")
	UItemBase* FindMatchItem(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;

	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove);
	UFUNCTION(Category = "Inventory")
	int32 RemoveAmountOfItem(UItemBase* ItemIn, int32 DesiredAmountToRemove);
	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(UItemBase* ItemIn, const int32 AmountToSplit);

	// getters
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };
	UFUNCTION(Category = "Inventory")
	FORCEINLINE int32 GetSlotCapacity() const { return InventorySlotsCapacity; };
	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; };

	// setters
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotCapacity) { InventorySlotsCapacity = NewSlotCapacity; };
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity;};

	// �κ��丮 ������Ʈ ��������Ʈ
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	virtual void BeginPlay() override;

	FItemAddResult HandelNonStackableItems(UItemBase* InputItem);
	int32 HandelStackableItems(UItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateWeightAddAmount(UItemBase* ItemIn, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(UItemBase* StackableItem, int32 InitialRequestedAddAmount);

	void AddNewItem(UItemBase* Item, const int32 AmountToAdd);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;
		
};
