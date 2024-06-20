#include "Library/GameSaveManager.h"

#include "ProjectDGameInstance.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/GadgetComponent.h"
#include "Characters/Components/InventoryComponent.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Common/UseColor.h"
#include "GameFramework/PlayerStart.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/MySaveGame.h"
#include "Pooling/ItemPool.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"
#include "UserInterface/Skill/PlayerSkillWidget.h"
#include "World/SaveLoad/SaveLoadObject.h"

// Sets default values
AGameSaveManager::AGameSaveManager()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemPool = CreateDefaultSubobject<UItemPool>( TEXT( "ItemPool" ) );
}

void AGameSaveManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName , FName SaveName, FName LevelName, 
	FVector Location , TArray<UItemBase*> ItemBases, bool UseLocation )
{
	switch (SaveType)
	{
	case ESaveType::SAVE_AUTO:
		SaveGameAsync( Character, "PlayerAutoSave", "PlayerAutoSave", LevelName, static_cast<int32>(ESaveType::SAVE_AUTO) , Location, ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_MAIN:
		SaveGameAsync( Character, "PlayerMainSave" , "PlayerMainSave" , LevelName, static_cast<int32>(ESaveType::SAVE_MAIN) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_1:
		SaveGameAsync( Character, SaveSlotName , SaveName , LevelName, static_cast<int32>(ESaveType::SAVE_1) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_2:
		SaveGameAsync( Character, SaveSlotName , SaveName , LevelName, static_cast<int32>(ESaveType::SAVE_2) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_3:
		SaveGameAsync( Character, SaveSlotName , SaveName , LevelName, static_cast<int32>(ESaveType::SAVE_3) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_4:
		SaveGameAsync( Character, SaveSlotName , SaveName , LevelName, static_cast<int32>(ESaveType::SAVE_4) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_5:
		SaveGameAsync( Character, SaveSlotName , SaveName , LevelName, static_cast<int32>(ESaveType::SAVE_5) , Location , ItemBases, UseLocation );
		break;
	case ESaveType::SAVE_END:
		break;
	}

}

void AGameSaveManager::SaveGame(AProjectDCharacter* Character, ESaveType SaveType, FString SaveSlotName, FName SaveName,
	FName LevelName, FVector Location, TArray<UItemBase*> ItemBases, bool UseLocation, 
	FString QuickSlot1, FString QuickSlot2, FString QuickSlot3, FString QuickSlot4)
{
	switch (SaveType)
	{
	case ESaveType::SAVE_AUTO:
		SaveGameAsync( Character , "PlayerAutoSave" , "PlayerAutoSave" , LevelName , static_cast<int32>(ESaveType::SAVE_AUTO) , 
			Location , ItemBases , UseLocation, QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_MAIN:
		SaveGameAsync( Character , "PlayerMainSave" , "PlayerMainSave" , LevelName , static_cast<int32>(ESaveType::SAVE_MAIN) , 
			Location, ItemBases , UseLocation, QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_1:
		SaveGameAsync( Character , SaveSlotName, SaveName , LevelName , static_cast<int32>(ESaveType::SAVE_1) , 
			Location , ItemBases , UseLocation, QuickSlot1, QuickSlot2, QuickSlot3, QuickSlot4);
		break;
	case ESaveType::SAVE_2:
		SaveGameAsync( Character , SaveSlotName , SaveName , LevelName , static_cast<int32>(ESaveType::SAVE_2) , 
			Location , ItemBases , UseLocation, QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_3:
		SaveGameAsync( Character , SaveSlotName , SaveName , LevelName , static_cast<int32>(ESaveType::SAVE_3) ,
			Location , ItemBases , UseLocation , QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_4:
		SaveGameAsync( Character , SaveSlotName , SaveName , LevelName , static_cast<int32>(ESaveType::SAVE_4) ,
			Location , ItemBases , UseLocation , QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_5:
		SaveGameAsync( Character , SaveSlotName , SaveName , LevelName , static_cast<int32>(ESaveType::SAVE_5) ,
			Location , ItemBases , UseLocation , QuickSlot1 , QuickSlot2 , QuickSlot3 , QuickSlot4 );
		break;
	case ESaveType::SAVE_END:
		break;
	}
}

void AGameSaveManager::LoadGame( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName, bool UseLocation, bool UseThread, bool OpenLevel )
{
	LoadGameAsync( Character, SaveType, SaveSlotName, UseLocation, UseThread , OpenLevel );
}

void AGameSaveManager::BeginPlay()
{
	Super::BeginPlay();

	ItemPool->CreateItem( 110 );

	SaveLoadObject = GetWorld()->SpawnActor<ASaveLoadObject>(ASaveLoadObject::StaticClass());
}

void AGameSaveManager::SaveGameAsync( AProjectDCharacter* Character , FString SaveSlotName , FName SaveName , FName LevelName ,
		int32 SaveIndex , FVector Location , TArray<UItemBase*> ItemBases , bool UseLocation )
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
				int32 Quantity = ItemBases[i]->GetQuantity();

				if(!Quantity)
					++Quantity;

				if (int32* ElemValue = ItemMap.Find( ItemName ))
					*ElemValue += Quantity;
				else
					ItemMap.Add( ItemBases[i]->GetTextData().Name.ToString() , Quantity );
			}
		}

		SaveGameInstance->SaveStruct.SaveName = SaveName;
		SaveGameInstance->SaveStruct.LevelName = LevelName;

		if(UseLocation)
			SaveGameInstance->SaveStruct.Location = Location;
		else
			if(AActor* PlayerStart = UGameplayStatics::GetActorOfClass( GetWorld() , APlayerStart::StaticClass() ))
				SaveGameInstance->SaveStruct.Location = PlayerStart->GetActorLocation();

			
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

void AGameSaveManager::SaveGameAsync(AProjectDCharacter* Character, FString SaveSlotName, FName SaveName,
	FName LevelName, int32 SaveIndex, FVector Location, TArray<UItemBase*> ItemBases, bool UseLocation,
	FString QuickSlot1, FString QuickSlot2, FString QuickSlot3, FString QuickSlot4)
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>( UGameplayStatics::CreateSaveGameObject( UMySaveGame::StaticClass() ) );

	if (SaveGameInstance)
	{
		/** Save file data **/
		SaveGameInstance->SaveSlotName = SaveSlotName;
		SaveGameInstance->SaveIndex = SaveIndex;

		TMap<FString , int32> ItemMap;

		for (int32 i = 0; i < ItemBases.Num(); ++i)
		{
			if (ItemBases[i])
			{
				FString ItemName = ItemBases[i]->GetTextData().Name.ToString();
				int32 Quantity = ItemBases[i]->GetQuantity();

				if (!Quantity)
					++Quantity;

				if (int32* ElemValue = ItemMap.Find( ItemName ))
					*ElemValue += Quantity;
				else
					ItemMap.Add( ItemBases[i]->GetTextData().Name.ToString() , Quantity );
			}
		}

		SaveGameInstance->SaveStruct.SaveName = SaveName;
		SaveGameInstance->SaveStruct.LevelName = LevelName;
		SaveGameInstance->SaveStruct.IsUseLocation = UseLocation;

		SaveGameInstance->SaveStruct.QuickSlotKey1 = QuickSlot1;
		SaveGameInstance->SaveStruct.QuickSlotKey2 = QuickSlot2;
		SaveGameInstance->SaveStruct.QuickSlotKey3 = QuickSlot3;
		SaveGameInstance->SaveStruct.QuickSlotKey4 = QuickSlot4;

		

		if (UseLocation)
		{
			SaveGameInstance->SaveStruct.Location = Location;
			SaveGameInstance->SaveStruct.Rotation = Character->GetCameraBoom()->GetComponentRotation();

		}
		else
			if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass( GetWorld() , APlayerStart::StaticClass() ))
				SaveGameInstance->SaveStruct.Location = PlayerStart->GetActorLocation();


		SaveGameInstance->SaveStruct.ItemBases = ItemMap;

		UGadgetComponent* GadgetComponent = Character->GetGadgetComp();

		if (UItemBase* Head = GadgetComponent->GetEquippedItem( EItemType::Head ))
		{
			SaveGameInstance->SaveStruct.EquippedItems.Add( EItemType::Head , Head->GetTextData().Name.ToString() );
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

		UProjectDGameInstance* GameInstance = Cast<UProjectDGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );

		SaveGameInstance->SaveStruct.CanUseColor = GameInstance->GetCanUseColor();
		SaveGameInstance->SaveStruct.ToToAutoSaveData = GameInstance->GetToToAutoSaveData();
		SaveGameInstance->SaveStruct.PlayerSkillLevel = GameInstance->GetPlayerSkillLevel();

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


void AGameSaveManager::LoadGameAsync( AProjectDCharacter* Character , ESaveType SaveType , FString SaveSlotName, bool UseLocation, bool UseThread, bool OpenLevel )
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

					if(LoadedGameInstance->SaveStruct.LevelName == FName( "Openinig" ))
						return;

					if (LoadedGameInstance->SaveStruct.LevelName != FName( "None" ) && OpenLevel)
					{
						UGameplayStatics::OpenLevel( GetWorld() , LoadedGameInstance->SaveStruct.LevelName );
						return;
					}
						

					if(UseLocation && !LoadedGameInstance->SaveStruct.Location.IsNearlyZero() && LoadedGameInstance->SaveStruct.IsUseLocation)
					{
						Character->SetActorLocation( LoadedGameInstance->SaveStruct.Location );
						Character->GetCameraBoom()->SetRelativeRotation( LoadedGameInstance->SaveStruct.Rotation );
					}
					else
					{
						if (AActor* PlayerStart = UGameplayStatics::GetActorOfClass( GetWorld() , APlayerStart::StaticClass() ))
							LoadedGameInstance->SaveStruct.Location = PlayerStart->GetActorLocation();

					}


					for(auto& ItemData : LoadedGameInstance->SaveStruct.ItemBases)
					{
						UItemBase* ItemBase = NewObject<UItemBase>();
						ItemBase->CreateItemCopy( ItemPool->GetItem( ItemData.Key ) );

						int32 StackSize = ItemBase->GetNumericData().MaxStackSize;

						while (ItemData.Value)
						{
							if (ItemBase)
							{
								if(!ItemBase->GetNumericData().bIsStackable)
								{
									ItemBase->SetQuantity( 1 , false );
									Character->GetInventory()->HandelAddItem( ItemBase );
									break;
								}


								if (ItemData.Value > StackSize)
								{
									ItemBase->SetQuantity( StackSize , false );
									ItemData.Value -= StackSize;
								}
								else
								{
									ItemBase->SetQuantity( ItemData.Value , false );
									Character->GetInventory()->HandelAddItem( ItemBase );
									break;
								}

								Character->GetInventory()->HandelAddItem( ItemBase );

								ItemBase = NewObject<UItemBase>();
								ItemBase->CreateItemCopy( ItemPool->GetItem( ItemData.Key ) );
							}
							else
							{
								UE_LOG( LogTemp , Error , TEXT( "AGameSaveManager::LoadGameAsync Load Failed -> ItemPool" ) );
							}
						}
					}

					GetWorld()->GetTimerManager().SetTimerForNextTick([this, Character, LoadedGameInstance]()
					{
						UQuickSlotWidget* Widget1 = Character->GetPlayerDefaultsWidget()->GetMainQuickSlot()->GetQuickSlotWidget1();
						UQuickSlotWidget* Widget2 = Character->GetPlayerDefaultsWidget()->GetMainQuickSlot()->GetQuickSlotWidget2();
						UQuickSlotWidget* Widget3 = Character->GetPlayerDefaultsWidget()->GetMainQuickSlot()->GetQuickSlotWidget3();
						UQuickSlotWidget* Widget4 = Character->GetPlayerDefaultsWidget()->GetMainQuickSlot()->GetQuickSlotWidget4();

						if(LoadedGameInstance->SaveStruct.QuickSlotKey1.IsEmpty())
						{
							Widget1->ReleaseQuickSlot( Widget1 );
						}
						else
						{
							Widget1->SetPreItemName( LoadedGameInstance->SaveStruct.QuickSlotKey1 );

							Widget1->QuantityCalled.Execute( LoadedGameInstance->SaveStruct.QuickSlotKey1 ,
							Character->GetInventory()->FindItemQuantity( LoadedGameInstance->SaveStruct.QuickSlotKey1 ) );

							Widget1->SetItemIcon();
						}

						if (LoadedGameInstance->SaveStruct.QuickSlotKey2.IsEmpty())
						{
							Widget2->ReleaseQuickSlot( Widget2 );
						}
						else
						{
							Widget2->SetPreItemName( LoadedGameInstance->SaveStruct.QuickSlotKey2 );

							Widget2->QuantityCalled.Execute( LoadedGameInstance->SaveStruct.QuickSlotKey2 ,
							Character->GetInventory()->FindItemQuantity( LoadedGameInstance->SaveStruct.QuickSlotKey2 ) );

							Widget2->SetItemIcon();
						}

						if (LoadedGameInstance->SaveStruct.QuickSlotKey3.IsEmpty())
						{
							Widget3->ReleaseQuickSlot( Widget3 );
						}
						else
						{
							Widget3->SetPreItemName( LoadedGameInstance->SaveStruct.QuickSlotKey3 );

							Widget3->QuantityCalled.Execute( LoadedGameInstance->SaveStruct.QuickSlotKey3 ,
							Character->GetInventory()->FindItemQuantity( LoadedGameInstance->SaveStruct.QuickSlotKey3 ) );

							Widget3->SetItemIcon();
						}

						if (LoadedGameInstance->SaveStruct.QuickSlotKey4.IsEmpty())
						{
							Widget4->ReleaseQuickSlot( Widget4 );
						}
						else
						{
							Widget4->SetPreItemName( LoadedGameInstance->SaveStruct.QuickSlotKey4 );

							Widget4->QuantityCalled.Execute( LoadedGameInstance->SaveStruct.QuickSlotKey4 ,
							Character->GetInventory()->FindItemQuantity( LoadedGameInstance->SaveStruct.QuickSlotKey4 ) );

							Widget4->SetItemIcon();
						}
					});

					FTimerHandle Handle;
					UProjectDGameInstance* GameInstance = Cast<UProjectDGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );

					GetWorld()->GetTimerManager().SetTimer( Handle, FTimerDelegate::CreateLambda([GameInstance, LoadedGameInstance, Character]()
					{
						for (auto& iter : LoadedGameInstance->SaveStruct.CanUseColor)
						{
							if (iter.Value)
							{
								if (iter.Key == EUseColor::RED)
								{
									Character->GetAttackComp()->SetSkillUseState( true , ESkillOpenType::NONE );
								}
								else if (iter.Key == EUseColor::YELLOW)
								{
									Character->GetAttackComp()->SetColorUseState( EUseColor::YELLOW , true );
								}
								else if (iter.Key == EUseColor::BLUE)
								{
									Character->GetAttackComp()->SetColorUseState( EUseColor::BLUE , true );
								}
							}


						}

					}), 0.1f, false);


					GameInstance->SetToToAutoSaveData( LoadedGameInstance->SaveStruct.ToToAutoSaveData );
					//APlayerGameMode* PlayerGameMode = Cast<APlayerGameMode>(GetWorld()->GetAuthGameMode());
					//PlayerGameMode->StartGameStory();


					for(int32 i = 0; i < LoadedGameInstance->SaveStruct.PlayerSkillLevel.Num(); ++i)
					{

						int32 SkillIndex = (i % 2) + 1;

						EUseColor Color = EUseColor::BLUE;

						if(i < 2)
							Color = EUseColor::RED;

						else if(i < 4)
							Color = EUseColor::YELLOW;

						GameInstance->SetPlayerSkillLevel( Color , SkillIndex, LoadedGameInstance->SaveStruct.PlayerSkillLevel[i] );
						Character->GetAttackComp()->InitSkillLevel();
						Character->GetAttackComp()->UpdateSkillLevel( SkillIndex , Character->GetAttackComp()->GetSkillInfo( Color , SkillIndex ) );
					}

					
					

					//Character->GetAttackComp()->InitCanUseColor();
					//Character->GetAttackComp()->InitSkillLevel();
					

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

