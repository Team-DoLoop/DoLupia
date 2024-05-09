// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStructs.h"
#include "ItemBase.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTD_API UItemBase : public UObject
{
	GENERATED_BODY()

	friend class UInventoryComponent;

public:
	UItemBase();

	void CreateItemCopy(const UItemBase* MyItemBase);

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == NumericData.MaxStackSize; };

	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	FORCEINLINE void SetID(FName _ID) { ID = _ID; }
	FORCEINLINE void SetItemType(EItemType _ItemType) { ItemType = _ItemType; }
	FORCEINLINE void SetItemQuality(EItemQuality _ItemQuality) { ItemQuality = _ItemQuality; }
	FORCEINLINE void SetItemStatistics(FItemStatistics _ItemStatistics) { ItemStatistics = _ItemStatistics; }
	FORCEINLINE void SetTextData(FItemTextData _TextData) { TextData = _TextData; }
	FORCEINLINE void SetNumericData(FItemNumericData _NumericData) { NumericData = _NumericData; }
	FORCEINLINE void SetAssetData(FItemAssetData _AssetData) { AssetData = _AssetData; }

	FORCEINLINE const FName& GetID() const { return ID; }
	FORCEINLINE EItemType GetItemType() { return ItemType; }
	FORCEINLINE int32 GetQuantity() const { return Quantity; } 
	FORCEINLINE EItemQuality GetItemQuality() const { return ItemQuality; }
	FORCEINLINE const FItemStatistics& GetItemStatistics() const { return ItemStatistics; }
	FORCEINLINE const FItemTextData& GetTextData() const { return TextData; }
	FORCEINLINE FItemNumericData& GetNumericData() { return NumericData; }
	FORCEINLINE const FItemAssetData& GetAssetData() const { return AssetData; }

	FORCEINLINE UInventoryComponent* GetOwningInventory() const { return OwningInventory; };
	FORCEINLINE void SetOwningInventory(UInventoryComponent* NewOwningInventory) { OwningInventory = NewOwningInventory; };

	UFUNCTION( Category = "Item" )
	virtual void Use( class AProjectDCharacter* Character );

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}


private:
	UPROPERTY()
	UInventoryComponent* OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	int32 Quantity;	// 인벤토리 최대치

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemTextData TextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemNumericData NumericData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
	FItemAssetData AssetData;

	bool bIsCopy;
	bool bIsPickup;

private:
	void ResetItemFlags();

};
