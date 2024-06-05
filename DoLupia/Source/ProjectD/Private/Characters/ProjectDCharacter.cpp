
// game
#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/InventoryComponent.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Characters/PlayerStat.h"
#include "Monsters/Monster.h"
#include "Quest/QuestLogComponent.h"
#include "Quest/QuestInventoryComponent.h"
#include "Quest/TestNPCCharacter.h"
#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/PlayerDefaults/PlayerDefaultsWidget.h"
#include "UserInterface/MainMenu.h"

#include "UserInterface/PlayerDefaults/QuickSlotWidget.h"
#include "World/Pickup.h"
#include "Data/WidgetData.h"
#include "Items/Sword/LongSword.h"

// engine
#include "AI/NavigationSystemBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Characters/ProjectDPlayerController.h"
#include "Characters/Animations/PlayerAnimInstance.h"
#include "Characters/Components/GadgetComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TimelineComponent.h"
#include "Elements/Framework/TypedElementQueryBuilder.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Components/MeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "Items/Cape/PlayerCape.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monsters/Drone/FloorAttack/FA_Blast_Base.h"
#include "NPC/NPCBase.h"
#include "NPC/QuestAcceptNPC.h"
#include "Quest/QuestGiver.h"
#include "UserInterface/Quest/NPCInteractionWidget.h"
#include "UserInterface/PlayerDefaults/PlayerBattleWidget.h"
#include "UserInterface/PlayerDefaults/PlayerHPWidget.h"
#include "UserInterface/PlayerDefaults/PlayerMPWidget.h"


AProjectDCharacter::AProjectDCharacter()
{
	// Mesh
	GetMesh()->SetWorldScale3D(FVector(3.0f));
	
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
	CameraBoom->TargetArmLength = 850.0f;
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

	// Collision
	GetCapsuleComponent()->SetCollisionProfileName( TEXT( "Player" ) );

	// Cape
	const FName& CapeSocket( TEXT( "CapeSocket" ) );
	CapeComp = CreateDefaultSubobject<UChildActorComponent>(TEXT("CapeComp"));
	CapeComp->SetupAttachment(GetMesh(), CapeSocket);
	CapeComp->SetRelativeLocation(FVector(0.0f, 10.0f, -9.4f));
	CapeComp->SetRelativeRotation(FRotator(40.0f, -90.0f, 180.0f));
	CapeComp->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.3333f));
	
	// State
	PlayerFSM = CreateDefaultSubobject<UPlayerFSMComp>(TEXT("PlayerFSM"));

	// Move
	moveComp = CreateDefaultSubobject<UPlayerMoveComp>(TEXT("MoveComp"));
	
	// Attack
	attackComp = CreateDefaultSubobject<UPlayerAttackComp>(TEXT("AttackComp"));
	
	// Inventory
	PlayerInventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
	PlayerInventory->SetWeightCapacity(50.0f);

	// Gadget
	Gadget = CreateDefaultSubobject<UGadgetComponent>(TEXT("Gadget"));

	// Interaction
	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 225.0f;
	
	// Quest
	PlayerQuest = CreateDefaultSubobject<UQuestLogComponent>(TEXT("PlayerQuest"));

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectDCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AProjectDPlayerController>(GetController());
	
	HUD = Cast<ADoLupiaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	PlayerStat = Cast<APlayerStat>(GetPlayerState());
	if(PlayerStat)
	{
		PlayerStat->initPlayerData();
		PlayerMaxHP = PlayerStat->GetMaxHP();
	}
	
	FOnTimelineFloat AimLerpAlphaValue;
	FOnTimelineEvent TimelineFinishedEvent;
	AimLerpAlphaValue.BindUFunction(this, FName("UpdateCameraTimeline"));
	TimelineFinishedEvent.BindUFunction(this, FName("CameraTimelineEnd"));

	if(AimingCameraTimeline && AimingCameraCurve)
	{
		AimingCameraTimeline->AddInterpFloat(AimingCameraCurve, AimLerpAlphaValue);
		AimingCameraTimeline->SetTimelineFinishedFunc(TimelineFinishedEvent);
	}

	if(!PlayerDefaultsWidget && PlayerDefaultsWidgetFactory)
	{
		PlayerDefaultsWidget = CreateWidget<UPlayerDefaultsWidget>(GetWorld(), PlayerDefaultsWidgetFactory );
		PlayerDefaultsWidget->AddToViewport(static_cast<int32>(ViewPortPriority::Main));

		PlayerBattleWidget = PlayerDefaultsWidget->GetPlayerBattleWidget();
		if(PlayerBattleWidget && PlayerStat)
		{
			PlayerBattleWidget->GetPlayerHPBar()->SetHPBar(PlayerStat->GetHP(), PlayerMaxHP);
			PlayerBattleWidget->GetPlayerMPBar()->SetMPBar(PlayerStat->GetMP(), PlayerStat->GetMaxMP());
		}
	}

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	GetMesh()->SetRenderCustomDepth( true );
	GetMesh()->CustomDepthStencilValue = 2;
	
	// 초기 장비 착용
	Gadget->InitEquip();
}

void AProjectDCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	HoveredQuickSlot();

	if(GetWorld()->TimeSince(InteractionData.LastInteractionCehckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
		//PerformTrace();
	}

	if(PlayerController->IsInputKeyDown(EKeys::N))
	{
		AFA_Blast_Base* Blast = GetWorld()->SpawnActor<AFA_Blast_Base>();
	}
}

void AProjectDCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
}

void AProjectDCharacter::TurnPlayer()
{
	if(!PlayerController) return;
	
	FHitResult Hit;
	bool bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if(bHitSuccessful)
	{
		FVector DirVec = Hit.ImpactPoint - GetActorLocation();
		FRotator TargetRot = UKismetMathLibrary::MakeRotFromXZ( DirVec , GetActorUpVector() );
		FRotator PlayerRot = GetActorRotation();
		FRotator TempRot = FRotator(PlayerRot.Pitch, TargetRot.Yaw, PlayerRot.Roll);
		SetActorRotation( TempRot);
	}
}
// <---------------------- UI ---------------------->

void AProjectDCharacter::OnSystemCall( const FText& Message ) const
{
	HUD->OnSystemCall( Message );
}

void AProjectDCharacter::OnSystemCallSoundCue( const FText& Message , USoundCue* SoundCue ) const
{
	HUD->OnSystemCallSoundCue( Message , SoundCue );
}

void AProjectDCharacter::OnSystemCallSoundWave( const FText& Message , USoundWave* SoundWave ) const
{
	HUD->OnSystemCallSoundWave( Message , SoundWave );
}

void AProjectDCharacter::ToggleMenu()
{
	if(!PlayerController) return;
	// FInputModeGameAndUI InputMode;
	// APlayerController* PlayerController = Cast<APlayerController>( GetController() );
	
	if(HUD->ToggleMenu())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus( PlayerDefaultsWidget->TakeWidget() );
		InputMode.SetWidgetToFocus( HUD->GetMainMeun()->TakeWidget());
		PlayerController->SetInputMode( InputMode );

		//InputMode.SetWidgetToFocus( HUD->GetMainMeun()->TakeWidget() );
	}
	else
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		PlayerController->SetInputMode( InputMode );
	}

	

	if(HUD->IsMenuVisible())
		StopAiming();
}

// 퀵 슬롯 자연스럽게 하기 위한 함수
void AProjectDCharacter::HoveredQuickSlot()
{
	if (PossibleChangeGameMode())
	{
		// 마우스 커서 위치를 감지
		float MouseX , MouseY;
		
		if (PlayerController->GetMousePosition( MouseX , MouseY ))
		{
			// 사용자 정의 함수로 마우스 위치 업데이트
			PlayerDefaultsWidget->QuickSlotMouseHoveredWidget( FVector2D( MouseX , MouseY ) );// ( FVector2D( MouseX , MouseY ) );
		}
	}
}

bool AProjectDCharacter::PossibleChangeGameMode()
{

	// 인벤토리 창이 켜지면
	if(HUD->IsMenuVisible())
		return false;

	if(SpecificActor)
	{
		UQuestGiver* QuestGiver = SpecificActor->GetQuestGiver();

		// 퀘스트 창이 뜨면
		if(QuestGiver->GetRewardQuestGiver() || QuestGiver->GetWidgetQuestGiver() || GetQuestLogComponent())
			return false;

		// 플레이어가 죽으면
		if(moveComp->PlayerDieUI)
			return false;

	}

	return true;
}

void AProjectDCharacter::UseQuickSlot(int32 SlotNumber)
{
	PlayerDefaultsWidget->UseQuickSlot( SlotNumber );
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

void AProjectDCharacter::TakeHit(EAttackType AttackType, EEffectAttackType EffectAttackType, float Damage)
{
	if(!PlayerFSM) return;
	
	if(AttackType == EAttackType::BASIC)
	{
		if(!(PlayerFSM->CanDamageState(EPlayerState::DAMAGE))) return;
		
	}

	if(AttackType == EAttackType::LYING)
	{
		if(!(PlayerFSM->CanLyingState(EPlayerState::LYING))) return;
		PlayerFSM->ChangePlayerState( EPlayerState::LYING );
		if(!PlayerAnim) return;
		PlayerAnim->PlayerLyingAnimation();
	}
	
	switch (EffectAttackType)
	{
	case EEffectAttackType::NONE : break;
	case EEffectAttackType::BLEED : break;
	case EEffectAttackType::POISON : break;
	}

	TakeDamage(Damage);
}

void AProjectDCharacter::TakeDamage(float Damage)
{
	// 데미지 받기
	int32 HP = PlayerStat->GetHP() - Damage;
	
	if (HP > 0)
	{
		// PlayerFSM->ChangePlayerState( EPlayerState::DAMAGE );
	}
	else
	{
		HP = 0;
		moveComp->Die();
	}

	PlayerStat->SetHP( HP );
	
	// UI 반영
	if(PlayerBattleWidget)
		PlayerBattleWidget->GetPlayerHPBar()->SetHPBar(HP, PlayerMaxHP);
	
	UE_LOG(LogTemp, Log, TEXT("HP : %d"), PlayerStat->GetHP() );
}

void AProjectDCharacter::LyingEnd()
{
	if(!PlayerFSM) return;
	PlayerFSM->ChangePlayerState(EPlayerState::IDLE);
}


// <---------------------- Interaction ---------------------->

void AProjectDCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCehckTime = GetWorld()->GetTimeSeconds();

	const FVector& TraceStart { GetPawnViewLocation()};
	const FVector& ViewVector { GetActorForwardVector() };
	const FVector& TraceEnd{TraceStart + ( ViewVector * InteractionCheckDistance) };

	const double LookDirection {FVector::DotProduct(GetActorForwardVector(), ViewVector)};

	if(LookDirection > 0.0)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;
		FRotator BoxRotation = FRotator::ZeroRotator;
		FVector BoxHalfSize = FVector( 50 , 50 , 50 );

		if(GetWorld()->SweepSingleByChannel( TraceHit , TraceStart , TraceEnd , FQuat( BoxRotation ) , ECC_Visibility , FCollisionShape::MakeBox( BoxHalfSize ) , QueryParams ))
		{
			FString name = TraceHit.GetActor()->GetName();
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
				InteractWidgetRemove();
				//UE_LOG( LogTemp , Warning , TEXT( "LookatActor : nullptr" ) );
			}
			// NPC 인터페이스 검사
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass() ))
			{
				LookAtActor = TraceHit.GetActor();
				InteractWidgetCreate();
				SpecificActor = Cast<ANPCBase>( LookAtActor );
				if (SpecificActor)
				{
					SpecificActor->LookAt(); // 인터페이스 메서드 호출
				}
			}
			else
			{
				LookAtActor = nullptr;
				InteractWidgetRemove();
				//UE_LOG( LogTemp , Warning , TEXT( "LookatActor: nullptr" ) );
			}
		}
		else
		{
			LookAtActor = nullptr;
			InteractWidgetRemove();
		}
	}
	else
	{
		LookAtActor = nullptr;
		NPCInteractGWidget->SetVisibility( ESlateVisibility::Hidden );
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
	//퀘스트 액터 확인
	if (LookAtActor && LookAtActor->GetClass()->ImplementsInterface( UQuestInteractionInterface::StaticClass() ))
	{
		IQuestInteractionInterface* QuestInterface = Cast<IQuestInteractionInterface>( LookAtActor );
		if (QuestInterface)
		{
			ANPCBase* npc = Cast<ANPCBase>( LookAtActor );

			if (npc)
			{
				UE_LOG( LogTemp , Error , TEXT( "NPC-TEST" ) );
				AQuestAcceptNPC* Questnpc = Cast<AQuestAcceptNPC>( LookAtActor );
				if(Questnpc)
				{
					UE_LOG( LogTemp , Error , TEXT( "QUESTNPC-TEST" ) );
					const FString& ActorObjectID = QuestInterface->InteractWith();
					//캐릭터가 베이스 한테
					OnObjectiveIDCalled.Broadcast( ActorObjectID , 1 );
				}
				else
				{
					npc->DialogWith();
				}
				
			}
			else
			{
				//이 interactWith가 많은 곳을 지나치는데 strageObject / NPC-> Giver
				const FString& ActorObjectID = QuestInterface->InteractWith();

				const FString& ActorName = LookAtActor->GetName(); // 액터의 이름을 가져옴
				UE_LOG( LogTemp , Warning , TEXT( "ActorName: %s" ) , *ActorName );

				//캐릭터가 베이스 한테
				OnObjectiveIDCalled.Broadcast( ActorObjectID , 1 );
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

UItemBase* AProjectDCharacter::SwitchEquipItem(UItemBase* ItemBase)
{
	return Gadget->ChangeItem(ItemBase);
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

		OnObjectiveIDCalled.Broadcast( ItemToDrop->GetTextData().Name.ToString() , -1*RemoveQuantity );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item to drop was somehos null"));
	}
}

//------------오브젝트 투명---------------
void AProjectDCharacter::PerformTrace()
{
	FVector Start = TopDownCameraComponent->GetComponentLocation();
	FVector End = Start + (TopDownCameraComponent->GetForwardVector() * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor( this );

	bool bHit = GetWorld()->LineTraceSingleByChannel( HitResult , Start , End , ECC_Visibility , CollisionParams );

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor != LastHitActor)
		{
			if (LastHitActor)
			{
				// 이전에 히트된 액터의 재질을 원래대로 복원
				UMeshComponent* MeshComponent = LastHitActor->FindComponentByClass<UMeshComponent>();
				if (MeshComponent)
				{
					for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
					{
						UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>( MeshComponent->GetMaterial( i ) );
						if (DynamicMaterial)
						{
							UE_LOG( LogTemp , Warning , TEXT( "Resetting opacity for: %s" ) , *LastHitActor->GetName() );
							DynamicMaterial->SetScalarParameterValue( TEXT( "Opacity" ) , 1.0f );
						}
						else
						{
							UE_LOG( LogTemp , Error , TEXT( "Failed to get dynamic material for: %s" ) , *LastHitActor->GetName() );
						}
					}
				}
			}

			// 현재 히트된 액터의 재질을 투명하게 설정
			UMeshComponent* MeshComponent = HitActor->FindComponentByClass<UMeshComponent>();
			if (MeshComponent)
			{
				for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
				{
					UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic( i );
					if (DynamicMaterial)
					{
						UE_LOG( LogTemp , Warning , TEXT( "Setting opacity for: %s" ) , *HitActor->GetName() );
						DynamicMaterial->SetScalarParameterValue( TEXT( "Opacity" ) , 0.0f );
					}
					else
					{
						// 기존 머티리얼을 동적 머티리얼 인스턴스로 변환
						UMaterialInterface* MaterialInterface = MeshComponent->GetMaterial( i );
						DynamicMaterial = UMaterialInstanceDynamic::Create( MaterialInterface , this );
						if (DynamicMaterial)
						{
							MeshComponent->SetMaterial( i , DynamicMaterial );
							UE_LOG( LogTemp , Warning , TEXT( "Converted to dynamic material and setting opacity for: %s" ) , *HitActor->GetName() );
							DynamicMaterial->SetScalarParameterValue( TEXT( "Opacity" ) , 0.0f );
						}
						else
						{
							UE_LOG( LogTemp , Error , TEXT( "Failed to create dynamic material for: %s" ) , *HitActor->GetName() );
						}
					}
				}
			}

			UE_LOG( LogTemp , Warning , TEXT( "Now hitting: %s" ) , *HitActor->GetName() );
			LastHitActor = HitActor;
		}
	}
	else
	{
		if (LastHitActor)
		{
			// 더 이상 히트되지 않은 경우, 이전에 히트된 액터의 재질을 원래대로 복원
			UMeshComponent* MeshComponent = LastHitActor->FindComponentByClass<UMeshComponent>();
			if (MeshComponent)
			{
				for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
				{
					UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>( MeshComponent->GetMaterial( i ) );
					if (DynamicMaterial)
					{
						UE_LOG( LogTemp , Warning , TEXT( "Resetting opacity for: %s" ) , *LastHitActor->GetName() );
						DynamicMaterial->SetScalarParameterValue( TEXT( "Opacity" ) , 1.0f );
					}
					else
					{
						UE_LOG( LogTemp , Error , TEXT( "Failed to get dynamic material for: %s" ) , *LastHitActor->GetName() );
					}
				}
			}

			UE_LOG( LogTemp , Warning , TEXT( "No longer hitting: %s" ) , *LastHitActor->GetName() );
			LastHitActor = nullptr;
		}
	}

	// 디버그용 선 그리기 (선택 사항)
	// DrawDebugLine( GetWorld() , Start , End , FColor::Green , false , 1 , 0 , 1 );
}

//--------------------- 상호작용 위젯 ------------------
void AProjectDCharacter::InteractWidgetCreate()
{
	if(!NPCInteractGWidget)
	{
		//상호작용 위젯 생성
		NPCInteractGWidget = CreateWidget<UNPCInteractionWidget>( GetWorld() , NPCInteractWidget );
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind) );
	}else
	{
		NPCInteractGWidget->AddToViewport( static_cast<uint32>(ViewPortPriority::Behind ));
	}
	
}

void AProjectDCharacter::InteractWidgetRemove()
{
	if(NPCInteractGWidget)
	{
		NPCInteractGWidget->RemoveFromParent();
	}
}