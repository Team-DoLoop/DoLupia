// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Inventory/InventoryItemSlot.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/ItemBase.h"
#include "UserInterface/Inventory/DragItemVisual.h"
#include "UserInterface/Inventory/InventoryTooltip.h"
#include "UserInterface/Inventory/ItemDragDropOperation.h"

void UInventoryItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(ToolTipFactory)
	{
		Tooltip = CreateWidget<UInventoryTooltip>(this, ToolTipFactory);
		Tooltip->SetInventoryItemSlotBeingHovered(this);
	}
}

void UInventoryItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UInventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	// 우클릭 예정
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		if(ItemReference)
		{

			UInventoryComponent* InventoryComponent = ItemReference->GetOwningInventory();
			AProjectDCharacter* MyCharacter = Cast<AProjectDCharacter>( InventoryComponent->GetOwner() );

			switch (ItemReference->GetItemType())
			{
			case EItemType::Top:
			case EItemType::Weapon:
			case EItemType::Shield:
			case EItemType::Head:
			case EItemType::Pants:
			case EItemType::Shoes:
			case EItemType::Spell:

				// 만약 내가 검을 장착하고 있다면?
					// -> 내가 장착할 검과 현재 장착한 검의 속성만 바꿔주고 적용하기

				// 검을 장착하고 있지 않다면?
					// -> 장착할 검의 속성을 그대로 넣어주고 인벤토리 아이템을 비워주기

				if (UItemBase* EquipItemBase = MyCharacter->SwitchEquipItem( ItemReference ))
				{
					ItemReference = EquipItemBase;
					RefreshItemSlot();
				}
				else
				{
					InventoryComponent->RemoveAmountOfItem( ItemReference , 1 );
					InventoryComponent->ReleaseInventory( ItemReference );
					ResetItemSlot();
				}

				break;
			case EItemType::Consumable:
				{
					/*const int32 Quantity = ItemReference->GetQuantity() - 1;
					ItemReference->SetQuantity( Quantity );*/
					ItemReference->GetOwningInventory()->RemoveAmountOfItem( ItemReference, 1);
					ItemReference->Use( MyCharacter );
					ItemReference->GetQuantity() == 0 ? ResetItemSlot() : RefreshItemSlot();
				}
					
				
				
				break;

			case EItemType::Quest:

				break;

			case EItemType::Mundane:

				break;
			default: ;
			}
		}
	}
	
	return Reply.Unhandled();
}

void UInventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if(DragItemVisualFactory && ItemReference)
	{
		const TObjectPtr<UDragItemVisual> DragItemVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualFactory);
		DragItemVisual->GetItemIcon()->SetBrushFromTexture(ItemReference->GetAssetData().Icon);

		ItemReference->GetNumericData().bIsStackable 
			? DragItemVisual->GetItemQuantity()->SetText(FText::AsNumber(ItemReference->GetQuantity()))
			: DragItemVisual->GetItemQuantity()->SetVisibility(ESlateVisibility::Collapsed);

		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();
		DragItemOperation->SetSourceItem(ItemReference);
		DragItemOperation->SetSourceInventory(ItemReference->GetOwningInventory());
		DragItemOperation->SetInventoryItemSlot(this);

		DragItemOperation->DefaultDragVisual = DragItemVisual;
		DragItemOperation->Pivot = EDragPivot::CenterLeft;
		
		OutOperation = DragItemOperation;
	}
}

void UInventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

bool UInventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if(const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>( InOperation ))
	{
		// 플레이어가 아이템을 드래그 앤 드랍 할 수 있도록 설정
		UInventoryItemSlot* InventoryItemSlot = ItemDragDrop->GetInventoryItemSlot();
		UItemBase* ItemBase = ItemDragDrop->GetSourceItem();
		if (ItemBase && !InventoryItemSlot->IsEmpty())
		{
			if(ItemBase == this->ItemReference)
				return false;

			UInventoryComponent* InventoryComponent = ItemBase->GetOwningInventory();
			InventoryComponent->SwapInventory(InventoryItemSlot, this);

			if (this->ItemReference)
			{
				InventoryItemSlot->SetItemReference( this->ItemReference );
				this->ItemReference = ItemBase;

				InventoryItemSlot->GetToolTip()->SetupTooltip();
				InventoryItemSlot->RefreshItemSlot();

				this->Tooltip->SetupTooltip();
				this->RefreshItemSlot();
			}
			else
			{
				InventoryItemSlot->SetItemReference( this->ItemReference );
				this->ItemReference = ItemBase;

				this->Tooltip->SetupTooltip();
				this->RefreshItemSlot();

				InventoryItemSlot->ResetItemSlot();
			}
			return true;

		}
	}


	return false;

	//return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}



void UInventoryItemSlot::RefreshItemSlot()
{
	if (ItemReference)
	{
		bIsEmpty = false;

		if(!Tooltip)
		{
			Tooltip = CreateWidget<UInventoryTooltip>( this , ToolTipFactory );
			UE_LOG(LogTemp, Error, TEXT("UInventoryItemSlot::RefreshItemSlot : Tooltip error"));
		}
			
			
		SetToolTip( Tooltip );


		//switch (ItemReference->GetItemQuality())
		//{
		//case EItemQuality::Shoddy:
		//	ItemBorder->SetBrushColor( OutlineColor1 );
		//	break;
		//case EItemQuality::Common:
		//	ItemBorder->SetBrushColor( OutlineColor2 );
		//	break;
		//case EItemQuality::Quality:
		//	ItemBorder->SetBrushColor( OutlineColor3 );
		//	break;
		//case EItemQuality::Masterwork:
		//	ItemBorder->SetBrushColor( OutlineColor4 );
		//	break;
		//case EItemQuality::Grandmaster:
		//	ItemBorder->SetBrushColor( OutlineColor5 ); // orange
		//	break;
		//default:;
		//}

		if(ItemReference->GetAssetData().IconMaterial)
		{
			UMaterialInstanceDynamic* ImageMatrialTemplate = UMaterialInstanceDynamic::Create(
				ItemReference->GetAssetData().IconMaterial,
				this
			);

			ItemIcon->SetBrushFromMaterial( ImageMatrialTemplate );

			Gradient( ImageMatrialTemplate );
			BackGround( ImageMatrialTemplate );
			Texture( ImageMatrialTemplate );
			Frame( ImageMatrialTemplate );

		}
		else
		{
			ItemIcon->SetBrushFromTexture( ItemReference->GetAssetData().Icon );
		}

		
		

		if (ItemReference->GetNumericData().bIsStackable)
		{
			ItemQuantity->SetVisibility( ESlateVisibility::Visible );
			ItemQuantity->SetText( FText::AsNumber( ItemReference->GetQuantity() ) );
			UE_LOG(LogTemp, Warning, TEXT( "UInventoryItemSlot::RefreshItemSlot() : %s" ) , *FText::AsNumber( ItemReference->GetQuantity()).ToString());

		}
		else
		{
			ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );
		}
	}
}

void UInventoryItemSlot::ResetItemSlot()
{
	ItemIcon->SetBrushFromTexture( nullptr );
	ItemQuantity->SetVisibility( ESlateVisibility::Collapsed );

	bIsEmpty = true;

	SetToolTip( nullptr );

	if (ItemReference)
		ItemReference = nullptr;
}

void UInventoryItemSlot::Gradient( UMaterialInstanceDynamic* MaterialInstanceDynamic )
{
	MaterialInstanceDynamic->SetVectorParameterValue( "BG gradient color 1" , ItemReference->GetMaterialGradient().Color1 );
	MaterialInstanceDynamic->SetVectorParameterValue( "BG Gradient color 2" , ItemReference->GetMaterialGradient().Color2 );
	MaterialInstanceDynamic->SetVectorParameterValue( "BG Gradient color 3" , ItemReference->GetMaterialGradient().Color3 );
	MaterialInstanceDynamic->SetVectorParameterValue( "BG gradient color 3 - active" , ItemReference->GetMaterialGradient().Color3_Active );

	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient glow min" , ItemReference->GetMaterialGradient().Glow_min );
	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient glow max" , ItemReference->GetMaterialGradient().Glow_max );

	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient noise intensity" , ItemReference->GetMaterialGradient().NoiseIntensity );

	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient pos color 1" , ItemReference->GetMaterialGradient().PosColor1 );
	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient pos color 2" , ItemReference->GetMaterialGradient().PosColor2 );
	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient pos color 3" , ItemReference->GetMaterialGradient().PosColor3 );

	MaterialInstanceDynamic->SetScalarParameterValue( "BG gradient size" , ItemReference->GetMaterialGradient().Size );

	MaterialInstanceDynamic->SetVectorParameterValue( "Noise panning speed" , ItemReference->GetMaterialGradient().NoisePanningSpeed );
}

void UInventoryItemSlot::BackGround( UMaterialInstanceDynamic* MaterialInstanceDynamic )
{
	MaterialInstanceDynamic->SetScalarParameterValue( "Box fill opacity" , ItemReference->GetMaterialBackGround().BoxFillOpacity );
	MaterialInstanceDynamic->SetScalarParameterValue( "Box scale" , ItemReference->GetMaterialBackGround().BoxScale );
	MaterialInstanceDynamic->SetScalarParameterValue( "Frame thickness" , ItemReference->GetMaterialBackGround().FrameThickness );
	MaterialInstanceDynamic->SetScalarParameterValue( "Glow max" , ItemReference->GetMaterialBackGround().GlowMax );
	MaterialInstanceDynamic->SetScalarParameterValue( "Glow min" , ItemReference->GetMaterialBackGround().GlowMin );
	MaterialInstanceDynamic->SetScalarParameterValue( "Noise intensity" , ItemReference->GetMaterialBackGround().NoiseIntensity );



}

void UInventoryItemSlot::Texture( UMaterialInstanceDynamic* MaterialInstanceDynamic )
{
	MaterialInstanceDynamic->SetTextureParameterValue( "ItemTexture" , ItemReference->GetAssetData().Icon );

	MaterialInstanceDynamic->SetScalarParameterValue( "Texture hovered additional scale" , ItemReference->GetMaterialTexture().HoveredAdditinal );

	MaterialInstanceDynamic->SetVectorParameterValue( "Texture offset" , ItemReference->GetMaterialTexture().Offset );
	MaterialInstanceDynamic->SetVectorParameterValue( "Texture offset - active" , ItemReference->GetMaterialTexture().Offset_Active );

	MaterialInstanceDynamic->SetScalarParameterValue( "Texture scale" , ItemReference->GetMaterialTexture().Scale );
	MaterialInstanceDynamic->SetScalarParameterValue( "Texture scale - active" , ItemReference->GetMaterialTexture().Scale_Active );
}

void UInventoryItemSlot::Frame( UMaterialInstanceDynamic* MaterialInstanceDynamic )
{
	//MaterialInstanceDynamic->SetTextureParameterValue( "ItemTexture" , ItemReference->GetAssetData().Icon );
}