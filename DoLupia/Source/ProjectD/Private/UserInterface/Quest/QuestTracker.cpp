// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Quest/QuestTracker.h"
#include "Quest/Quest_Base.h"
#include "Components/TextBlock.h"
#include <UserInterface/Quest/WidgetQuestLog_Objective.h>
#include "Components/VerticalBox.h"
#include "Quest/QuestLogComponent.h"

void UQuestTracker::NativePreConstruct()
{
    // 플레이어 컨트롤러 및 캐릭터 획득
    APlayerController* OwningPlayer = GetOwningPlayer();
    if (!IsObjectValid( OwningPlayer , "OwningPlayer" ))
    {
        return;
    }

    ACharacter* PlayerCharacter = OwningPlayer->GetCharacter();
    if (!IsObjectValid( PlayerCharacter , "PlayerCharacter" ))
    {
        return;
    }

    AProjectDCharacter* PlayerCharacterD = Cast<AProjectDCharacter>( PlayerCharacter );
    if (!IsObjectValid( PlayerCharacterD , "PlayerCharacterD" ))
    {
        return;
    }

    // QuestLogComponent 찾기
    QuestLogComp = Cast<UQuestLogComponent>( PlayerCharacterD->GetComponentByClass( UQuestLogComponent::StaticClass() ) );
    if (!IsObjectValid( QuestLogComp , "QuestLogComp" ))
    {
        return;
    }
}

void UQuestTracker::NativeConstruct()
{
    WidgetUpdate();
}

void UQuestTracker::NativeDestruct()
{
}

void UQuestTracker::WidgetUpdate()
{
    if (!IsValid( QuestActor ))
    {
        UE_LOG( LogTemp , Warning , TEXT( "QuestActor is null!" ) );
        return;
    }

    if (QuestActor)
    {
        //퀘스트 엑터에서 온 델리게이트 받기
        QuestActor->OnObjectiveHeard.BindDynamic( this , &UQuestTracker::OnObjectiveHeard );
        if (txt_QuestName)
        {
            FText QN_MyText = FText::FromString( QuestActor->QuestDetails.QuestName );

            // FText를 FString으로 변환하여 로그 출력
            UE_LOG( LogTemp , Error , TEXT( "Quest Name: %s" ) , *QN_MyText.ToString() );

            txt_QuestName->SetText( QN_MyText );
        }

        // Objectives를 추가하기 전에 기존 위젯을 클리어
        if (box_Objectives)
        {
            box_Objectives->ClearChildren();
        }

        if (QuestActor->QuestDetails.Stages.Num() > 0) // 배열이 비어 있지 않은지 확인
        {
            const auto& FirstStage = QuestActor->QuestDetails.Stages[0]; // 첫 번째 요소에 접근
            for (const auto& Objective : FirstStage.Objectives) // 범위 기반 for 루프
            {
                UWidgetQuestLog_Objective* ObjectiveWidget = CreateWidget<UWidgetQuestLog_Objective>( GetWorld() , Objective_Widget );
                if (IsValid( ObjectiveWidget ))
                {
                    ObjectiveWidget->ObjectiveData = Objective;
                    ObjectiveWidget->QuestActor = QuestActor;
                    box_Objectives->AddChildToVerticalBox( ObjectiveWidget );
                }
            }

            //반복 완료

            QuestLogComp->QuestCompleted.AddDynamic( this , &UQuestTracker::QuestCompleted );
        }
    }
}

void UQuestTracker::Update( AQuest_Base* UP_QuestActor )
{
    QuestActor = UP_QuestActor;

    WidgetUpdate();
}

void UQuestTracker::Remove()
{
    RemoveFromParent();
}

void UQuestTracker::QuestCompleted( AQuest_Base* QC_QuestActor)
{
    if (QuestActor == QC_QuestActor) {
        RemoveFromParent();
    }
}

void UQuestTracker::OnObjectiveHeard()
{
    Update( QuestActor );
}
