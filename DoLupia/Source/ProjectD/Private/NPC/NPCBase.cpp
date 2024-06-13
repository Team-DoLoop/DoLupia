// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCBase.h"
#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"
#include "Engine.h"
#include "AI/AIMarterialTestActor.h"
#include <Kismet/GameplayStatics.h>

#include "Blueprint/UserWidget.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Data/WidgetData.h"
#include "NPC/Animation/NPCAnim.h"
#include "Quest/QuestGiver.h"
#include "Quest/Dialogsystem/DialogComponent.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"

#include "MapIconComponent.h"

// Sets default values
ANPCBase::ANPCBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	QuestGiverComp = CreateDefaultSubobject<UQuestGiver>( TEXT( "QuestGiverComp" ) );
	DialogComp = CreateDefaultSubobject<UDialogComponent>( TEXT( "DialogComp" ) );

	// 초기화
	AIlib = nullptr;
	DialogNum = 0;
	anim = nullptr;
	gm = nullptr;

	this->SetActorScale3D( FVector(1.5f, 1.5f, 1.5f) );
	// Post Process depth 설정값
	//GetMesh()->SetRenderCustomDepth( true );

	//minimap icon
	// MapIconComponent makes the character appear on the minimap
	static ConstructorHelpers::FObjectFinder<UTexture2D> QuestGiveIcon( TEXT( "/MinimapPlugin/Textures/Icons/T_Icon_Quest1.T_Icon_Quest1" ) );
	static ConstructorHelpers::FObjectFinder<UTexture2D> QuestRewardsIcon( TEXT( "/MinimapPlugin/Textures/Icons/T_Icon_Quest2.T_Icon_Quest2" ) );
	MapIcon = CreateDefaultSubobject<UMapIconComponent>( TEXT( "MapIcon" ) );
	MapIcon->SetupAttachment( GetRootComponent() );
	// Set the player icon as texture
	MapIcon->SetIconTexture( QuestGiveIcon.Object );
	// The icon will rotate to represent the character's rotation
	MapIcon->SetIconRotates( false );
}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	anim = Cast<UNPCAnim>( this->GetMesh()->GetAnimInstance() );


	if (gm)
	{
		UE_LOG( LogTemp , Warning , TEXT( "gm - Load Success" ) );
	}
	else {
		UE_LOG( LogTemp , Warning , TEXT( "gm - Load Failed" ) );
	}
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
	AProjectDCharacter* player = Cast<AProjectDCharacter>( OtherActor );

	/*
	if (player)
	{
		AIlib = gm->GetAIConnectionLibrary();
		
		// 현재 활성 레벨을 world context object로 사용하여 AIlib 함수를 호출합니다.
		if (AIlib)
		{
			//BeginChat();
		}
		else {
			UE_LOG( LogTemp , Warning , TEXT( "AIlib - Load failed" ) );
		}
		NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}else
	{
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}
	*/
}

void ANPCBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (NPCInteractGWidget)
	{
		NPCInteractGWidget->RemoveFromParent();
	}
}

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
	UE_LOG( LogTemp , Warning , TEXT( "Message : [%s]" ) , *Message )

	gm->ReceiveNPCMsg( NPCConversation );

}

void ANPCBase::DialogWith()
{
	DialogComp->StartDialog( this , *NPCID , DialogNum );
	ChangeNPCStatus( stencilDepth );
	anim->bTalking = true;

	ChangePlayerState();
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
	
	ChangePlayerState();

	return QuestInterface->InteractWith();
}

void ANPCBase::LookAt()
{
}

void ANPCBase::ChangeNPCStatus(int32 depth)
{
	GetMesh()->SetRenderCustomDepth( true );
	GetMesh()->CustomDepthStencilValue = depth;
}

void ANPCBase::ChangePlayerState()
{
	// 플레이어 행동 가능하게
	if(AProjectDCharacter* Player = Cast<AProjectDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if(auto PlayerFSM = Player->GetPlayerFSMComp())
		{
			if(PlayerFSM->CanChangeState(EPlayerState::TALK_NPC))
				PlayerFSM->ChangePlayerState(EPlayerState::TALK_NPC);
		}
	}
}

void ANPCBase::HideNPC()
{
	this->SetActorHiddenInGame( true );
}

