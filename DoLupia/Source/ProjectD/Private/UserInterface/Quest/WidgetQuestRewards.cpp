// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/WidgetQuestRewards.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Characters/ProjectDPlayerController.h"
#include "Quest/QuestLogComponent.h"
#include "Characters/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/Quest/WidgetQuestLog_Objective.h"
#include <Components/Image.h>
#include "Components/HorizontalBox.h"
#include "Components/Spacer.h"
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerFSMComp.h"
#include <Components/SizeBoxSlot.h>
#include <Components/SizeBox.h>

#include "ProjectDGameInstance.h"
#include "Characters/PlayerStateBase.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Common/UseColor.h"
#include "Gamemode/PlayerGameMode.h"

void UWidgetQuestRewards::NativePreConstruct()
{
    GI = Cast<UProjectDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (!QuestDetails.QuestName.IsEmpty())
    {
        FText QN_MyText = FText::FromString( QuestDetails.QuestName );
        txt_QuestName->SetText( QN_MyText );
    }

    if (!QuestDetails.LogDescription.IsEmpty())
    {
        FText QD_MyText = FText::FromString( QuestDetails.LogDescription );
        txt_QuestDesc->SetText( QD_MyText );
    }

    if (QuestDetails.Stages.Num() > 0 && !QuestDetails.Stages[0].Description.IsEmpty())
    {
        FText SD_MyText = FText::FromString( QuestDetails.Stages[0].Description );
        txt_StageDesc->SetText( SD_MyText );
    }

    if (!ItemRewards.IsEmpty())
    {
        for (const auto& itemImage : ItemRewards)
        {
            if (itemImage == nullptr)  // itemImage가 null인지 확인
            {
                continue;
            }

            UTexture2D* IconTexture = itemImage->GetAssetData().Icon;

            if (IconTexture == nullptr)
            {
                continue;
            }

            // SizeBox 생성
            USizeBox* SizeBox = NewObject<USizeBox>( this );
            if (SizeBox)
            {
                // SizeBox의 크기 설정
                SizeBox->SetWidthOverride( 60.0f );
                SizeBox->SetHeightOverride( 60.0f );

                // UImage 생성
                UImage* RewardItemIcon = NewObject<UImage>( this );
                if (RewardItemIcon)
                {
                    RewardItemIcon->SetBrushFromTexture( IconTexture );
                    SizeBox->AddChild( RewardItemIcon );

                    // SizeBox를 HorizontalBox에 추가
                    box_RewardsItem->AddChild( SizeBox );

                    // Spacer 추가
                    USpacer* Spacer = NewObject<USpacer>( this );
                    if (Spacer)
                    {
                        Spacer->SetSize( FVector2D( 10.0f , 1.0f ) );  // Spacer 크기 설정
                        box_RewardsItem->AddChild( Spacer );
                    }
                }
            }
        }
    }

}

void UWidgetQuestRewards::NativeConstruct()
{
    if (btn_Accept)
    {
        btn_Accept->OnClicked.AddDynamic( this , &UWidgetQuestRewards::OnAcceptClicked );
    }

    /*if (btn_Decline)
    {
        btn_Decline->OnClicked.AddDynamic( this , &UWidgetQuestRewards::OnDeclineClicked );
    }*/
    

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

    if (PlayerControllerD) {
        FInputModeUIOnly InputMode;
        PlayerControllerD->SetInputMode( InputMode );
    }
}

void UWidgetQuestRewards::NativeDestruct()
{
    Super::NativeDestruct();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if (PlayerController)
    {
        auto PlayerControllerD = Cast<AProjectDPlayerController>( PlayerController );

        FInputModeGameOnly InputMode;
        InputMode.SetConsumeCaptureMouseDown(false);
        PlayerControllerD->SetInputMode( InputMode );
    }
}

void UWidgetQuestRewards::OnAcceptClicked()
{
    //AI 망토 이미지 적용
    auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
    auto AIlib = gm->GetAIConnectionLibrary();
    gm->ApplyAITxtP();
    //AI*/

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!IsValid( PlayerController ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerController is not valid." ) );
        return;
    }

    ACharacter* PlayerCharacter = Cast<ACharacter>( PlayerController->GetPawn() );
    if (!IsValid( PlayerCharacter ))
    {
        UE_LOG( LogTemp , Error , TEXT( "Quest_Base / BeginPlay / PlayerCharacter is not valid." ) );
        return;
    }

    AProjectDCharacter* PlayerCharacterD = Cast<AProjectDCharacter>( PlayerCharacter );

    // 캐릭터에서 QuestLogComponent를 찾습니다.
    UQuestLogComponent* QuestLogComp = Cast<UQuestLogComponent>( PlayerCharacterD->GetComponentByClass( UQuestLogComponent::StaticClass() ) );
    if (!IsValid( QuestLogComp ))
    {
        UE_LOG( LogTemp , Error , TEXT( "QuestLogComponent is invalid or not found on PlayerCharacter." ) );
        return;
    }

    QuestLogComp->CompleteQuest(QuestID);

    if (QuestID.IsNone())
    {
        UE_LOG( LogTemp , Error , TEXT( "Invalid QuestID _ WidgetQuestGiver" ) );
    }

    //아이템 삭제, 제공

    // UInventoryComponent 찾기
    UInventoryComponent* InvetoryComp = Cast<UInventoryComponent>( PlayerCharacterD->GetComponentByClass( UInventoryComponent::StaticClass() ) );

    //Delete(ObjectiveItems)

    /*
    //아이템 지울 게 있을 때
    auto RemoveItem = QuestDetails.Stages.GetData()->Objectives;
    if (!RemoveItem.IsEmpty())
    {
    	for (const auto& removeItem : RemoveItem)
	    {
	        FString ItemLog;
	        for (const auto& Pair : removeItem.ItemObjectives)
	        {
	            ItemLog += FString::Printf( TEXT( "(%s, %d) " ) , *Pair.Key , Pair.Value );
	        }
	        //UE_LOG( LogTemp , Warning , TEXT( "Removing item: %s" ) , *ItemLog );

	        InvetoryComp->HandelRemoveItem( removeItem.ItemObjectives );
	    }  
    }
    */


    //보상이 있을 때
    if(!ItemRewards.IsEmpty())
    {
		for (const auto& items : ItemRewards) {
        //보상 아이템 추가
        InvetoryComp->HandelAddItem( items);
		}    
    }
    
    // 위젯을 화면에서 제거합니다.
    RemoveFromParent();

    // 플레이어 행동 가능하게
    ChangePlayerStateIdle();
    
    if(QuestID == "1002" || QuestID == "2002" || QuestID == "2004")
    {
        // 퀘스트 보상으로 스킬 해제
        if( QuestID == "1002")
        {
            PlayerCharacterD->GetAttackComp()->SetSkillUseState( true , ESkillOpenType::QUEST );
            PlayerCharacterD->GetAttackComp()->SetColorUseState( EUseColor::RED , true );
        }
        else if (QuestID == "2002")
        {
            PlayerCharacterD->GetAttackComp()->SetColorUseState( EUseColor::YELLOW , true );
        }
        else if (QuestID == "2004")
        {
            PlayerCharacterD->GetAttackComp()->SetColorUseState( EUseColor::BLUE , true );
        }
        
        GI->ExecuteTutorial(QuestDetails.AutoStory.QuestStoryType, -1, QuestDetails.AutoStory.QuestStoryID);
    }
}

void UWidgetQuestRewards::ChangePlayerStateIdle()
{
    // 플레이어 행동 가능하게
    if (AProjectDCharacter* Player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) ))
    {
        if (auto PlayerFSM = Player->GetPlayerFSMComp())
        {
            if (PlayerFSM->CanChangeState( EPlayerState::IDLE ))
                PlayerFSM->ChangePlayerState( EPlayerState::IDLE );
        }
    }
}

/*void UWidgetQuestRewards::OnDeclineClicked()
{
    RemoveFromParent();
}*/

