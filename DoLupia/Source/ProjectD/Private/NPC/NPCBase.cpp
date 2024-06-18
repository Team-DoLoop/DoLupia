// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"
#include "Engine.h"
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Data/WidgetData.h"
#include "NPC/Animation/NPCAnim.h"
#include "Quest/QuestGiver.h"
#include "Quest/Dialogsystem/DialogComponent.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"
#include "UserInterface/NPC/FadeInOutWidget.h"

#include "MapIconComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/PlayerDefaults/MainQuickSlotWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"

// Sets default values
ANPCBase::ANPCBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiverComp = CreateDefaultSubobject<UQuestGiver>( TEXT( "QuestGiverComp" ) );
	DialogComp = CreateDefaultSubobject<UDialogComponent>( TEXT( "DialogComp" ) );
	CameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT("Camera"));
	CameraPosition = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraPosition"));
	TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComp" ) );

	CameraComponent->SetupAttachment( GetRootComponent() );
	CameraPosition->SetupAttachment(GetRootComponent());

	// 초기화
	AIlib = nullptr;
	DialogNum = 0;
	anim = nullptr;
	gm = nullptr;

	this->SetActorScale3D( FVector(1.5f, 1.5f, 1.5f) );

	//minimap icon
	// MapIconComponent makes the character appear on the minimap
	static ConstructorHelpers::FObjectFinder<UTexture2D> QuestGiveIcon( TEXT( "/Game/Asset/Widget/MiniMap/request.request" ) );
	static ConstructorHelpers::FObjectFinder<UTexture2D> QuestRewardsIcon( TEXT( "/Game/Asset/Widget/MiniMap/speech-bubble.speech-bubble" ) );
	MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
	MapIcon->SetupAttachment( GetRootComponent() );
	// Set the player icon as texture
	MapIcon->SetIconTexture( QuestRewardsIcon.Object );
	// The icon will rotate to represent the character's rotation
	MapIcon->SetIconRotates( false );
	MapIcon->SetIconVisible( false );

	// Quest Tag
	CurrentQuestTag = "";
	OwnQuestTag = NAME_None;
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	anim = Cast<UNPCAnim>( this->GetMesh()->GetAnimInstance() );

	if (gm)
	{
		// 델리게이트 구독
		gm->OnNextNPCQuestTagReceived.AddDynamic( this , &ANPCBase::OnNextNPCQuestTagReceived );
	}

	if (MapIcon)
	{
		MapIcon->OnIconDestroyed.AddDynamic( this , &ANPCBase::OnDestroyNPCIcon );
	}

	if (DialogNum == 501)
	{
		anim->bDie = true;
	}

	if (PlayerCamCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction( this , FName( "OnMoveCamera" ) );
		TimelineComp->AddInterpFloat( PlayerCamCurve , ProgressFunction );

		FOnTimelineEvent TimelineFinishedFunction;
		TimelineFinishedFunction.BindUFunction( this , FName( "OnTimelineFinished" ) );
		TimelineComp->SetTimelineFinishedFunc( TimelineFinishedFunction );
	}

	Target = Cast<AProjectDCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	OriginalViewTarget = GetWorld()->GetFirstPlayerController()->GetViewTarget();
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::NotifyActorBeginOverlap( AActor* OtherActor )
{
	if (NPCInteractWidget)
	{
		NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}
	else
	{
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}
}

void ANPCBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (NPCInteractGWidget)
	{
		NPCInteractGWidget->RemoveFromParent();
	}
}

/* AI Chatbot 관련 주석처리
void ANPCBase::BeginChat()
{
	if (AIlib) {
		AIlib->OnWebApiResponseReceived.AddDynamic( this , &ANPCBase::CallNPCMessageDelegate );

		FString testStr = "이게 무슨 일이죠?";
		AIlib->SendNPCConversationToServer( testStr );

		
	}
	else {
		UE_LOG( LogTemp , Warning , TEXT( "AIlib - First Load failed" ) );
	}
}

void ANPCBase::CallNPCMessageDelegate( FString Message )
{
	NPCConversation = Message;
	gm->ReceiveNPCMsg( NPCConversation );

}
*/

void ANPCBase::DialogWith()
{
	if(bCanTalk)
	{
		DialogComp->StartDialog( this , *NPCID , DialogNum );

		// Dialog 503 일 때, AI서버 요청
		if (DialogNum == 501)
		{
			AIlib = gm->GetAIConnectionLibrary();
			AIlib->SendPImgToSrv( 2004 );
		}


		anim->bTalking = true;

		ChangePlayerState();

		if (!TimelineTrigger)
		{
			TimelineComp->PlayFromStart();
			TimelineTrigger = true;
		}

		if (FadeInOutWidgetFactory)
		{
			FadeInOutWidget = CreateWidget<UFadeInOutWidget>( GetWorld() , FadeInOutWidgetFactory );
			FadeInOutWidget->AddToViewport( static_cast<int32>(ViewPortPriority::Quest) );
			FadeInOutWidget->SetVisibility( ESlateVisibility::HitTestInvisible );
			FadeInOutWidget->FadeInOut();
			Target->GetPlayerBattleWidget()->SetVisibility( ESlateVisibility::Hidden );
			Target->GetPlayerDefaultsWidget()->GetMainQuickSlot()->SetVisibility( ESlateVisibility::Hidden );
		}
	}
	
}

FString ANPCBase::InteractWith()
{
	// 먼저 QuestGiverComp가 유효한지 확인
	if (QuestGiverComp == nullptr)
	{
		UE_LOG( LogTemp , Error , TEXT( "QuestGiverComp is null." ) );
		return FString( TEXT( "QuestGiverComp is null." ) );
	}

	// QuestGiverComp가 UQuestInteractionInterface를 구현하는지 확인
	if (!QuestGiverComp->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass() ))
	{
		return FString( TEXT( "QuestGiverComp does not implement UQuestInteractionInterface." ) );
	}

	// 인터페이스로 캐스팅 시도
	IQuestInteractionInterface* QuestInterface = Cast<IQuestInteractionInterface>( QuestGiverComp );

	if (QuestInterface == nullptr)
	{
		UE_LOG( LogTemp , Error , TEXT( "Failed to cast QuestGiverComp to IQuestInteractionInterface." ) );
		return FString( TEXT( "Failed to cast QuestGiverComp to IQuestInteractionInterface." ) );
	}

	FString Result = QuestInterface->InteractWith();

	ChangePlayerState();

	return Result;
}

void ANPCBase::LookAt()
{
}

void ANPCBase::OnNextNPCQuestTagReceived( FString NextQuestTag )
{
	if (OwnQuestTag.ToString() == NextQuestTag)
	{
		UpdateNPCStatus();
		bCanTalk = true;
	}
}

void ANPCBase::OnDestroyNPCIcon( UMapIconComponent* icon )
{
	icon->DestroyComponent(true);
}

void ANPCBase::UpdateNPCStatus()
{
	if( gm && gm->GetNxtQuestTag() != "")
	{
		if (OwnQuestTag == FName( gm->GetNxtQuestTag() ))
		{
			// 태그 값이 일치하면 상태 변경 로직 추가
			UE_LOG( LogTemp , Log , TEXT( "NPC with tag %s received matching Quest ID: %s" ) , *OwnQuestTag.ToString() , *CurrentQuestTag );
			
			ChangeNPCColor( 4 );
		} else
		{
			
		}
	}
}

void ANPCBase::ChangeNPCColor(int32 depth)
{
	if(bCheckIcon) return;

	UE_LOG( LogTemp , Error , TEXT( "npc - colortest : %d" ), depth );
	GetMesh()->SetRenderCustomDepth( true );
	GetMesh()->SetCustomDepthStencilValue( depth );
	MapIcon->SetIconVisible( true ); 
	bCheckIcon = true;
}

void ANPCBase::ChangePlayerState()
{
	if(auto PlayerFSM = Target->GetPlayerFSMComp())
	{
		if(PlayerFSM->CanChangeState(EPlayerState::TALK_NPC))
			PlayerFSM->ChangePlayerState(EPlayerState::TALK_NPC);
	}
}

void ANPCBase::HideNPC()
{	
	//this->MapIcon->SetIconVisible( false );
	MapIcon->OnIconDestroyed.RemoveDynamic( this , &ANPCBase::OnDestroyNPCIcon );

	if(MapIcon)
	{
		MapIcon->DestroyComponent( true );
		MapIcon = nullptr;
	}
	

	this->SetActorHiddenInGame( true );
	this->SetActorEnableCollision( ECollisionEnabled::NoCollision );
}

FString ANPCBase::GetNxtQuestID() const
{
	return NxtQuestID;
	/*
	if (QuestGiverComp)
	{
		return QuestGiverComp->QuestData.RowName.ToString();
	}
	return LexToString(NAME_None); // 유효하지 않은 경우
	*/
}

void ANPCBase::SwitchToPlayerCamera()
{
	if(OriginalViewTarget)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend( Target, 1.0f );
		Target->GetPlayerBattleWidget()->SetVisibility( ESlateVisibility::HitTestInvisible );
		Target->GetPlayerDefaultsWidget()->GetMainQuickSlot()->SetVisibility( ESlateVisibility::SelfHitTestInvisible );

		if (auto PlayerFSM = Target->GetPlayerFSMComp())
		{
			if (PlayerFSM->CanChangeState( EPlayerState::TALK_NPC ))
				PlayerFSM->ChangePlayerState( EPlayerState::IDLE );
		}
	}
}


void ANPCBase::OnMoveCamera( float Value )
{
	const FVector& TargetLocation = Target->GetActorLocation();
	const FVector& MyLocation = CameraPosition->GetComponentLocation();

	// 타겟의 위치를 보간하여 업데이트
	FVector NewLocation = FMath::Lerp( TargetLocation , FVector( MyLocation.X , MyLocation.Y , TargetLocation.Z ) , Value );
	Target->SetActorLocation( NewLocation );

	// NPC의 방향으로 회전 벡터를 계산
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation( TargetLocation , GetActorLocation() );

	// 회전 보간하여 설정
	Target->SetActorRotation( FMath::Lerp( Target->GetActorRotation(), LookAtRotation, Value)  );

	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend( this , 1.0f );

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]()
	{
		OnTimelineFinished();
	}), 1.f, false);
}

void ANPCBase::OnTimelineFinished()
{
	Target->GetCharacterMovement()->Velocity = FVector(0.0, 0.0, 0.0);
	TimelineComp->Stop();
}


