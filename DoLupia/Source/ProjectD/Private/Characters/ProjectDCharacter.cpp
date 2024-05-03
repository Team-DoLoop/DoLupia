﻿
// game
#include "Characters/ProjectDCharacter.h"
#include "UserInterface/DoLupiaHUD.h"
#include "World/Pickup.h"

// engine
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Characters/Components/InventoryComponent.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Components/TimelineComponent.h"
#include "Elements/Framework/TypedElementQueryBuilder.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/TestNPCCharacter.h"


AProjectDCharacter::AProjectDCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Player Settings
	BaseEyeHeight = 76.f;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	AimingCameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimingCameraTimeline"));
	DefaultCameraLocation = FVector{0.0, 0.0, 0.0};
	AimingCameraLocation = FVector{0.0, 0.0, 300.0 };
	CameraBoom->SocketOffset = DefaultCameraLocation;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	// State
	PlayerFSM = CreateDefaultSubobject<UPlayerFSMComp>(TEXT("PlayerFSM"));

	// Move
	moveComp = CreateDefaultSubobject<UPlayerMoveComp>(TEXT("moveComp"));
	
	// Attack
	attackComp = CreateDefaultSubobject<UPlayerAttackComp>(TEXT("AttackComp"));
	
	// Inventory
	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
	PlayerInventory->SetWeightCapacity(50.0f);

	// Interaction
	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 225.0f;
	
	// Quest
	PlayerQuest = CreateDefaultSubobject<UQuestLogComponent>(TEXT("PlayerQuest"));
	QuestInteractable =  CreateDefaultSubobject<UQuestInteractionInterface>( TEXT( "QuestInterface" ) );

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectDCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<ADoLupiaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FOnTimelineFloat AimLerpAlphaValue;
	FOnTimelineEvent TimelineFinishedEvent;
	AimLerpAlphaValue.BindUFunction(this, FName("UpdateCameraTimeline"));
	TimelineFinishedEvent.BindUFunction(this, FName("CameraTimelineEnd"));

	if(AimingCameraTimeline && AimingCameraCurve)
	{
		AimingCameraTimeline->AddInterpFloat(AimingCameraCurve, AimLerpAlphaValue);
		AimingCameraTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}
}

void AProjectDCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if(GetWorld()->TimeSince(InteractionData.LastInteractionCehckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

	// <---------------------- UI ---------------------->
void AProjectDCharacter::ToggleMenu()
{
	HUD->ToggleMenu();

	if(HUD->IsMenuVisible())
		StopAiming();
}

	// <---------------------- Attack ---------------------->
void AProjectDCharacter::Aim()
{
	// 만약 메인 위젯이 켜지지 않았다면 줌인을 하자.

	if(!HUD->IsMenuVisible())
	{
		bIsAiming = true;
		//GetCharacterMovement()->MaxWalkSpeed = 200.f;

		if(AimingCameraTimeline)
			AimingCameraTimeline->PlayFromStart();
	}
}

void AProjectDCharacter::StopAiming()
{

	// 만약 메인 위젯이 켜지지 않았다면 줌인을 하자.

	if(bIsAiming)
	{
		bIsAiming = false;
		//GetCharacterMovement()->MaxWalkSpeed = 500.f;

		if(AimingCameraTimeline)
			AimingCameraTimeline->Reverse();
	}
}

void AProjectDCharacter::UpdateCameraTimeline(const float TimelineValue) const
{
	const FVector CameraLocation = FMath::Lerp(DefaultCameraLocation, AimingCameraLocation, TimelineValue);
	CameraBoom->SocketOffset = CameraLocation;
}

void AProjectDCharacter::CameraTimelineEnd()
{
	if(AimingCameraTimeline)
	{
		if(AimingCameraTimeline->GetPlaybackPosition() != 0.0f)
		{
			//HUD->Disp
		}
	}
}


	// <---------------------- Interaction ---------------------->
void AProjectDCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCehckTime = GetWorld()->GetTimeSeconds();

	const FVector& TraceStart {GetPawnViewLocation()};
	const FVector& ViewVector { GetViewRotation().Vector() };
	const FVector& TraceEnd{TraceStart + ( ViewVector * InteractionCheckDistance) };

	const double LookDirection {FVector::DotProduct(GetActorForwardVector(), ViewVector)};

	if(LookDirection > 0.0)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if(GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			FString name = TraceHit.GetActor()->GetName();
			UE_LOG( LogTemp , Error , TEXT( "%s" ) , *name );

			if(TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
			{

				if(TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					FoundInteractable(TraceHit.GetActor());
					return;
				}

				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}
			}
			else
			{
				LookAtActor = nullptr;
				UE_LOG( LogTemp , Warning , TEXT( "LookatActor : nullptr" ) );
			}
			//NPC 인식
			if(TraceHit.GetActor()->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass()))
			{
				LookAtActor = TraceHit.GetActor();
				
				ATestNPCCharacter* SpecificActor = Cast<ATestNPCCharacter>( LookAtActor );
				if (SpecificActor)
				{
					UE_LOG( LogTemp , Error , TEXT( "LookatActor : Interface found" ) );
					SpecificActor->LookAt(); // 인터페이스 메서드 호출
				}
			}else
			{
				LookAtActor = nullptr;
				UE_LOG( LogTemp , Error , TEXT( "LookatActor : nullptr" ) );
			}
		}else
		{
			LookAtActor = nullptr;
		}
	}
	NoInteractionableFound();
}

void AProjectDCharacter::FoundInteractable(AActor* NewInteractable)
{
	if(IsInteracting())
	{
		EndInteract();
	}

	if(InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->GetInteractableData());

	TargetInteractable->BeginFocus();
}

void AProjectDCharacter::NoInteractionableFound()
{
	if(IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}

	if (InteractionData.CurrentInteractable)
	{
		if(IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		// HUD占쏙옙 Interaction widget占쏙옙 占쏙옙占쏙옙占쏙옙
		HUD->HideInteractionWidget();

		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AProjectDCharacter::BeginInteract()
{
	// 占쏙옙호占쌜울옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙호占쌜울옙 占쏙옙占쏙옙 占쏙옙占승울옙 占싣뱄옙占싶듸옙 占쏙옙占쏙옙占쏙옙占?占십았댐옙占쏙옙 확占쏙옙占싹쇽옙占쏙옙.
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();

			if(FMath::IsNearlyZero(TargetInteractable->GetInteractableData().InteractionDuration,  0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction, 
				this, 
				&AProjectDCharacter::Interact, 
				TargetInteractable->GetInteractableData().InteractionDuration,
				false);
			}
		}
	}
	//퀘스트 액터 확인 코드
	if (IsValid( LookAtActor ))
	{
		if (LookAtActor->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass() )) // 인터페이스 구현 여부 확인
		{
			// 액터에서 인터페이스 인스턴스를 얻습니다.
			IQuestInteractionInterface* QuestInterface = Cast<IQuestInteractionInterface>( LookAtActor );
			if (QuestInterface)
			{
				// 인터페이스 메서드 호출
				QuestInterface->InteractWith();
				UE_LOG( LogTemp , Log , TEXT( "InteractWith() called on LookAtActor" ) );

				// 특정 아이디 또는 기타 데이터를 얻습니다.
				FString ActorObjectID = LookAtActor->GetFName().ToString();

				OnObjectiveIDCalled.Broadcast( ActorObjectID ); // 이 이벤트로 브로드캐스트
			}
		}
	}
}

void AProjectDCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if(IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AProjectDCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}

void AProjectDCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		HUD->UpdateInteractionWidget(&TargetInteractable->GetInteractableData());
	}
}

	// <---------------------- Item ---------------------->
void AProjectDCharacter::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{
	if(PlayerInventory->FindMatchItem(ItemToDrop))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		const FVector& SpawnLocation { GetActorLocation() + (GetActorForwardVector() * 50.f)};
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		const int32 RemoveQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);

		Pickup->InitializeDrop(ItemToDrop, RemoveQuantity);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehos null"));
	}
}
