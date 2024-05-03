

#include "World/Pickup.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Items/ItemBase.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickUpMesh->SetSimulatePhysics(true);
	SetRootComponent(PickUpMesh);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
	
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangePropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(ChangePropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID))
	{
		if(ItemDataTable)
		{
			if(const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				PickUpMesh->SetStaticMesh(ItemData->AssetData.Mesh);
			}
		}
	}
}

void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);

		ItemReference->SetID(ItemData->ID);
		ItemReference->SetItemType(ItemData->ItemType);
		ItemReference->SetItemQuality(ItemData->ItemQuality);
		ItemReference->SetItemStatistics(ItemData->ItemStatistics);
		ItemReference->SetTextData(ItemData->TextData);
		ItemReference->SetNumericData(ItemData->NumericData);
		ItemReference->SetAssetData(ItemData->AssetData);

		// 만약 MaxStacksize 가 1보다 작다면 인벤토리에 쌓이지 않게 한다.
		FItemNumericData& ItemNumericData = ItemReference->GetNumericData();
		ItemNumericData.bIsStackable = ItemNumericData.MaxStackSize > 1;
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		PickUpMesh->SetStaticMesh(ItemData->AssetData.Mesh);

		UpdateInteractableData();
	}
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;

	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
	ItemReference->GetNumericData().Weight = ItemToDrop->GetItemSingleWeight();
	ItemReference->SetOwningInventory(nullptr);
	PickUpMesh->SetStaticMesh(ItemToDrop->GetAssetData().Mesh);
	UpdateInteractableData();
}

void APickup::BeginFocus()
{
	if(PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
	if (PickUpMesh)
	{
		PickUpMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(AProjectDCharacter* PlayerCharacter)
{
	if(PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

void APickup::UpdateInteractableData()
{

	const FItemTextData& TextData = ItemReference->GetTextData();

	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = TextData.InteractionText;
	InstanceInteractableData.Name = TextData.Name;
	InstanceInteractableData.Quantity = ItemReference->GetQuantity();
	InteractableData = InstanceInteractableData;
}

void APickup::TakePickup(const AProjectDCharacter* Taker)
{
	if(!IsPendingKillPending())
	{
		if(ItemReference)
		{
			if(UInventoryComponent* PlayerInventory = Taker->GetInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandelAddItem(ItemReference);

				switch (AddResult.OperationResult)
				{
					case EItemAddResult::IAR_NoItemAdded:

						break;
					case EItemAddResult::IAR_PartialAmoutItemAdded:
						UpdateInteractableData();
						Taker->UpdateInteractionWidget();
						break;
					case EItemAddResult::IAR_AllItemAdded:
						Destroy();
						break;

					default: ;
				}

				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Inventory component is null!"));
			}

			// 인벤토리 항목에 추가한 결과에 따라
			// 아이템을 파괴하거나 집어간다.
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null!"));
		}
	}
}

