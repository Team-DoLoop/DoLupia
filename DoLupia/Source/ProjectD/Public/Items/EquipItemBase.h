// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipItemBase.generated.h"

class UItemBase;
class UStaticMesh;
enum class EItemType : uint8;

UCLASS(Abstract)
class PROJECTD_API AEquipItemBase : public AActor
{
	GENERATED_BODY()

public:
	AEquipItemBase();

	void ReceiveItemData(UItemBase* NewItemBase, bool UsedSubMesh = false);
	FORCEINLINE UItemBase* GetItemBase() { return ItemBase; }
	FORCEINLINE class UStaticMeshComponent* GetItemStaticMesh() const { return ItemStaticMesh; }

	void ChangeAvatar( UStaticMesh* ItemMesh );
	void UnUsedAvatar();

protected:
	virtual void BeginPlay() override;



protected:
	UPROPERTY( VisibleAnywhere )
	TObjectPtr<UItemBase> ItemBase;

	UPROPERTY( VisibleAnywhere )
	class UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY( VisibleAnywhere )
	UStaticMesh* OriginalMesh;

	bool USeAvatar = false;
};
