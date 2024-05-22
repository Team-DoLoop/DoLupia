

#include "World/Pickup.h"
#include "World/Pickup.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Items/ItemBase.h"
#include "Spawner/ItemSpawner.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickUpMesh->SetSimulatePhysics(true);
	SetRootComponent(PickUpMesh);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Item Collision");
	SphereComponent->InitSphereRadius( 50.0f );
	SphereComponent->SetCollisionProfileName( TEXT( "OverlapAllDynamic" ) );
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);

	if (ItemDataTable)
	{
		if (const FItemData* ItemData = ItemDataTable->FindRow<FItemData>( DesiredItemID , DesiredItemID.ToString() ))
		{
			PickUpMesh->SetStaticMesh( ItemData->AssetData.Mesh );
		}
	}

	if(SphereComponent)
	{
		SphereComponent->OnComponentBeginOverlap.AddDynamic( this , &APickup::BezierBeginOverlap );
	}

	ItemSpawner = GetWorld()->SpawnActor<AItemSpawner>( FVector::ZeroVector , FRotator::ZeroRotator );
	ItemSpawner->AttachToActor( this , FAttachmentTransformRules::SnapToTargetNotIncludingScale );
	ItemSpawner->AddItemID( "regeneration potion" );
	ItemSpawner->AddItemID( "regeneration potion" );
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

void APickup::StartMovement(FVector StartPoint, FVector ActorSpeed )
{
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
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
		// 테스트용
		TArray<UItemBase*> Test = ItemSpawner->SpawnItemAll();

		FVector StartPosition = GetActorLocation();

		for(int32 i = 0; i < Test.Num(); ++i)
		{
			// 위치와 회전 값을 XOR 연산하여 고유한 시드 값 생성
			// 나중에 확률 추가하려면 따로 구현 해야함.
			uint32 Seed = StartPosition.X;
			Seed = Seed ^ (uint32)StartPosition.Y;
			Seed = Seed ^ (uint32)StartPosition.Z;

			FRandomStream RandomStream( Seed );
			FVector ActorSpeed =  FVector
			( 
				RandomStream.RandRange( -300 , 300 ), 
				RandomStream.RandRange( 300 , 800 ), 
				RandomStream.RandRange( -300 , 300 )
			);


			FTimerHandle TimerHandle;
			ItemReference = Test[i];
			InitializeDrop( ItemReference, 1);
			ItemSpawner->MoveItemAlongCurve( this, this,  StartPosition, ActorSpeed, RandomStream.RandRange(45, 80) * 0.01f);
		}
			

		

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
						//Destroy();
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

void APickup::BezierBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

