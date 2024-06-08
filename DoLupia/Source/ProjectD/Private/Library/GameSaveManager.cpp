#include "Library/GameSaveManager.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Library/MySaveGame.h"
#include "Pooling/ItemPool.h"

// Sets default values
AGameSaveManager::AGameSaveManager()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemPool = CreateDefaultSubobject<UItemPool>( TEXT( "ItemPool" ) );
}

void AGameSaveManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName , FName SaveName, FVector Location , TArray<UItemBase*> ItemBases )
{
	switch (SaveType)
	{
	case ESaveType::SAVE_AUTO:
		SaveGameAsync( Character, "PlayerAutoSave", "PlayerAutoSave", static_cast<int32>(ESaveType::SAVE_AUTO) , Location, ItemBases );
		break;
	case ESaveType::SAVE_MAIN:
		SaveGameAsync( Character, "PlayerMainSave" , "PlayerMainSave" , static_cast<int32>(ESaveType::SAVE_MAIN) , Location , ItemBases );
		break;
	case ESaveType::SAVE_1:
		SaveGameAsync( Character, SaveSlotName , SaveName , static_cast<int32>(ESaveType::SAVE_1) , Location , ItemBases );
		break;
	case ESaveType::SAVE_2:
		SaveGameAsync( Character, SaveSlotName , SaveName , static_cast<int32>(ESaveType::SAVE_2) , Location , ItemBases );
		break;
	case ESaveType::SAVE_3:
		SaveGameAsync( Character, SaveSlotName , SaveName , static_cast<int32>(ESaveType::SAVE_3) , Location , ItemBases );
		break;
	case ESaveType::SAVE_4:
		SaveGameAsync( Character, SaveSlotName , SaveName , static_cast<int32>(ESaveType::SAVE_4) , Location , ItemBases );
		break;
	case ESaveType::SAVE_5:
		SaveGameAsync( Character, SaveSlotName , SaveName , static_cast<int32>(ESaveType::SAVE_5) , Location , ItemBases );
		break;
	case ESaveType::SAVE_END:
		break;
	}
}

void AGameSaveManager::LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName )
{
	LoadGameAsync( Character, SaveType, SaveSlotName );
}

void AGameSaveManager::BeginPlay()
{
	Super::BeginPlay();

	ItemPool->CreateItem( 110 );
}

void AGameSaveManager::SaveGameAsync( AProjectDCharacter* Character, FString SaveSlotName, FName SaveName, int32 SaveIndex, FVector Location, TArray<UItemBase*> ItemBases)
{

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>( UGameplayStatics::CreateSaveGameObject( UMySaveGame::StaticClass() ) );

	if (SaveGameInstance)
	{
		/** Save file data **/
		SaveGameInstance->SaveSlotName = SaveSlotName;
		SaveGameInstance->SaveIndex = SaveIndex;

		TMap<FString, int32> ItemMap;

		for(int32 i = 0; i < ItemBases.Num(); ++i)
		{
			if(ItemBases[i])
			{
				FString ItemName = ItemBases[i]->GetTextData().Name.ToString();
				const int32 Quantity = ItemBases[i]->GetQuantity();

				if (int32* ElemValue = ItemMap.Find( ItemName ))
					*ElemValue += Quantity;
				else
					ItemMap.Add( ItemBases[i]->GetTextData().Name.ToString() , Quantity );
			}
		}

		SaveGameInstance->SaveStruct.SaveName = SaveName;
		SaveGameInstance->SaveStruct.Location = Location;
		SaveGameInstance->SaveStruct.ItemBases = ItemMap;

		UGadgetComponent* GadgetComponent = Character->GetGadgetComp();

		if(UItemBase* Head = GadgetComponent->GetEquippedItem( EItemType::Head ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Head, Head->GetTextData().Name.ToString());
		}
			
		if (UItemBase* Top = GadgetComponent->GetEquippedItem( EItemType::Top ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Top , Top->GetTextData().Name.ToString() );
		}
			
		if (UItemBase* Pants = GadgetComponent->GetEquippedItem( EItemType::Pants ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Pants , Pants->GetTextData().Name.ToString() );
		}
				
		if (UItemBase* Shoes = GadgetComponent->GetEquippedItem( EItemType::Shoes ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Shoes , Shoes->GetTextData().Name.ToString() );
		}
			
		if (UItemBase* Weapon = GadgetComponent->GetEquippedItem( EItemType::Weapon ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Weapon , Weapon->GetTextData().Name.ToString() );
		}


		//AsyncTask( ENamedThreads::AnyBackgroundThreadNormalTask , [SaveGameInstance]()
		{
			bool bSuccess = UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->SaveIndex );

			//AsyncTask( ENamedThreads::GameThread , [bSuccess]()
			{
				if (bSuccess)
				{
					UE_LOG( LogTemp , Log , TEXT( "Game saved successfully." ) );
				}
				else
				{
					UE_LOG( LogTemp , Error , TEXT( "Failed to save game." ) );
				}
			} //);
		} //);

		//UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->SaveIndex );
	}
	else
	{
		UE_LOG( LogTemp , Error , TEXT( "SaveGameInstance is nullptr" ) );
	}

	

}

void AGameSaveManager::LoadGameAsync( AProjectDCharacter* Character, ESaveType SaveType , FString SaveSlotName )
{
	if(Character)
	{
		//if(UseThread)
		//{
		//	
		//}

		//AsyncTask( ENamedThreads::GameThread , [&SaveType , &SaveSlotName, Character]()
		{
			USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot( SaveSlotName , static_cast<int32>(SaveType) );

			//AsyncTask( ENamedThreads::GameThread , [LoadedGame, Character]()
			{
			if (LoadedGame)
			{
				if (UMySaveGame* LoadedGameInstance = Cast<UMySaveGame>( LoadedGame ))
				{
					UE_LOG( LogTemp , Log , TEXT( "Game loaded successfully. SaveName: %s, Location: %s" ) ,
						*LoadedGameInstance->SaveStruct.SaveName.ToString() , *LoadedGameInstance->SaveStruct.Location.ToString() );

					Character->SetActorLocation( LoadedGameInstance->SaveStruct.Location );

					for(auto& ItemData : LoadedGameInstance->SaveStruct.ItemBases)
					{
						UItemBase* ItemBase = ItemPool->GetItem( ItemData.Key );

						if(ItemBase)
						{
							if(!ItemData.Value)
								++ItemData.Value;

							ItemBase->SetQuantity( ItemData.Value , false );
							Character->GetInventory()->HandelAddItem( ItemBase );
						}
						else
						{
							UE_LOG(LogTemp, Error, TEXT("AGameSaveManager::LoadGameAsync Load Failed -> ItemPool"));
						}
					}
						

					for(const auto& EquippedItem : LoadedGameInstance->SaveStruct.EquippedItems)
					{

						UGadgetComponent* GadgetComponent = Character->GetGadgetComp();

						UItemBase* ItemBase = ItemPool->GetItem( EquippedItem.Value );

						if(GadgetComponent)
						{
							if (ItemBase)
								GadgetComponent->ChangeItem( ItemBase );
							else
								UE_LOG( LogTemp , Error , TEXT( "AGameSaveManager::LoadGameAsync Load Failed -> ItemPool" ) );
						}
						else
						{
							UE_LOG( LogTemp , Error , TEXT( "AGameSaveManager::LoadGameAsync Load Failed -> UGadgetComponent" ) );
						}

					}
					
				}
			}
			else
			{
				UE_LOG( LogTemp , Error , TEXT( "Failed to load game." ) );
			}
			} //);
		} //);
	}


}

