// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/ProjectDPlayerController.h"

#include "EngineUtils.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/ProjectDCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "AI/AIMarterialTestActor.h"
#include "Characters/PlayerStateBase.h"
#include "Characters/Components/PlayerAttackComp.h"
#include "Characters/Components/PlayerFSMComp.h"
#include "Characters/Components/PlayerMoveComp.h"
#include "Characters/Components/PlayerTutorialComp.h"
#include "Engine/LocalPlayer.h"
#include "UserInterface/DoLupiaHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Quest/WidgetQuestLog.h"
#include "Data/WidgetData.h"
#include "Library/AIConnectionLibrary.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AProjectDPlayerController::AProjectDPlayerController()
{
	bShowMouseCursor = true;

	DefaultMouseCursor = EMouseCursor::Default;
	CurrentMouseCursor = EMouseCursor::Default;
}


void AProjectDPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());
}


// <---------------------- Input ---------------------->

void AProjectDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AProjectDPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AProjectDPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AProjectDPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		/*
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AProjectDPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AProjectDPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AProjectDPlayerController::OnTouchReleased);
		*/
		
		// Evasion
		EnhancedInputComponent->BindAction(EvasionAction, ETriggerEvent::Started, this, &AProjectDPlayerController::Evasion);

		// Interact
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &AProjectDPlayerController::BeginInteract);
		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::EndInteract);

		// UI
		EnhancedInputComponent->BindAction(ToggleAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ToggleMenu);

		EnhancedInputComponent->BindAction( QuickSlot1Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 0 );
		EnhancedInputComponent->BindAction( QuickSlot2Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 1 );
		EnhancedInputComponent->BindAction( QuickSlot3Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 2 );
		EnhancedInputComponent->BindAction( QuickSlot4Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 3 );
		EnhancedInputComponent->BindAction( QuickSlot5Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 4 );
		EnhancedInputComponent->BindAction( QuickSlot6Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 5 );
		EnhancedInputComponent->BindAction( QuickSlot7Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 6 );
		EnhancedInputComponent->BindAction( QuickSlot8Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 7 );
		EnhancedInputComponent->BindAction( QuickSlot9Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 8 );
		EnhancedInputComponent->BindAction( QuickSlot0Action , ETriggerEvent::Started , this , &AProjectDPlayerController::UseQuickSlot , 9 );

		//QuestUI
		//EnhancedInputComponent->BindAction( QuestTabAction , ETriggerEvent::Started , this , &AProjectDPlayerController::QuestLogMenu );

		// Attack
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Started, this, &AProjectDPlayerController::Aim);
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::StopAiming);


		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ExecuteSkill, 0);							// Click
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProjectDPlayerController::ExecuteSkill, 0);							// Click
		
		
		EnhancedInputComponent->BindAction(SwingSkillAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ExecuteSkill, 1);						// Q
		EnhancedInputComponent->BindAction(SwingSkillAction, ETriggerEvent::Triggered, this, &AProjectDPlayerController::ChargingSkill, 1);						// Q
		EnhancedInputComponent->BindAction(SwingSkillAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::ChargingEndSkill, 1);						// Q
		
		EnhancedInputComponent->BindAction(SpellSkillAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ExecuteSkill, 2);						// W Start
		EnhancedInputComponent->BindAction(SpellSkillAction, ETriggerEvent::Completed, this, &AProjectDPlayerController::QuitSkill, 2);						// W End
		

		EnhancedInputComponent->BindAction(CastingHitDownSkillAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ExecuteSkill, 3);			// E

		EnhancedInputComponent->BindAction(UltSkillAction, ETriggerEvent::Started, this, &AProjectDPlayerController::ExecuteSkill, 4);						// R

		// Test
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Started, this, &AProjectDPlayerController::TestAnyFunction);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


// <---------------------- Test ---------------------->

void AProjectDPlayerController::TestAnyFunction()
{
	if(!ControlledCharacter) return;
	
	// Die Test
	// ControlledCharacter->moveComp->Die();
	
	// TakeDamage Test
	//ControlledCharacter->TakeHit(EAttackType::LYING,31.0f);

	/*
	// AI Test
	auto gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	auto AIlib = gm->GetAIConnectionLibrary();

	TestCount++;
	if(TestCount == 1)
	{
		int32 tmpNum = 1;
		AIlib->SendPImgToSrv( tmpNum );
	}
	else
	{
		TestCount = 0;

		gm->ApplyAITxtP();
	}
	*/

	// 첫 퀘스트(아무색 없다가 Red라도 생기는 경우) or 무기 장착한 경우
	if(TestCount == 0)
	{
		ControlledCharacter->GetAttackComp()->SetSkillUseState(true, QUEST);

		// 각 색깔 열리게
		ControlledCharacter->GetAttackComp()->SetColorUseState(EUseColor::RED, true);
		ControlledCharacter->GetAttackComp()->SetColorUseState(EUseColor::YELLOW, true);
		ControlledCharacter->GetAttackComp()->SetColorUseState(EUseColor::BLUE, true);
		TestCount++;
	}

	else
	{
		ControlledCharacter->GetTutorialComp()->NextTutorial();
	}

	// ControlledCharacter->TakeEffectAttackHit(EEffectAttackType::ELECTRIC);
}

	
// <---------------------- Move ---------------------->

void AProjectDPlayerController::OnInputStarted()
{
	if(!ControlledCharacter) return;
	StopMovement();
}

// Triggered every frame when the input is held down
void AProjectDPlayerController::OnSetDestinationTriggered()
{
	if(!ControlledCharacter) return;
	ControlledCharacter->moveComp->OnSetDestinationTriggered();
}

void AProjectDPlayerController::OnSetDestinationReleased()
{
	if(!ControlledCharacter) return;
	ControlledCharacter->moveComp->OnSetDestinationReleased();
}

/*
// Triggered every frame when the input is held down
void AProjectDPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AProjectDPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}
*/

void AProjectDPlayerController::Evasion()
{
	OnInputStarted();
	
	// 회피기
	if(!ControlledCharacter) return;
	ControlledCharacter->moveComp->Evasion();

	
	// 스킬 업그레이드
	// ControlledCharacter->GetAttackComp()->GetSkillUpgradePoint(EUseColor::RED, 1);
}

// <---------------------- UI ---------------------->

void AProjectDPlayerController::ToggleMenu()
{
	// AProjectDCharacter* ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());
	
	if (ControlledCharacter)
		ControlledCharacter->ToggleMenu();
}

bool AProjectDPlayerController::IsHoverd()
{
	return Cast<ADoLupiaHUD>( GetHUD() )->GetMainMeun()->IsHovered();
}

void AProjectDPlayerController::UseQuickSlot(int32 QuickSlotNumber)
{
	if (ControlledCharacter)
		ControlledCharacter->UseQuickSlot( QuickSlotNumber );
}


// <---------------------- Interaction ---------------------->

void AProjectDPlayerController::BeginInteract()
{
	// AProjectDCharacter* ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());

	if (ControlledCharacter)
		ControlledCharacter->BeginInteract();
		
}

void AProjectDPlayerController::EndInteract()
{
	// AProjectDCharacter* ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());

	if(ControlledCharacter)
		ControlledCharacter->EndInteract();

}



// <---------------------- Attack ---------------------->

void AProjectDPlayerController::Aim()
{
	// AProjectDCharacter* ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());

	if (ControlledCharacter)
		ControlledCharacter->Aim();

}

void AProjectDPlayerController::StopAiming()
{
	// AProjectDCharacter* ControlledCharacter = Cast<AProjectDCharacter>(GetCharacter());

	if (ControlledCharacter)
		ControlledCharacter->StopAiming();

}

/*
void AProjectDPlayerController::Attack()
{
	if(!ControlledCharacter) return;
	ControlledCharacter->attackComp->Attack();

	if (ControlledCharacter->GetPlayerFSMComp()->GetCurrentState() == EPlayerState::ATTACK)
		OnInputStarted();
	else
	{
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown( true );
		SetInputMode( InputMode );
	}

}
*/

void AProjectDPlayerController::QuitSkill(int32 SkillIndex)
{
	if(!ControlledCharacter) return;

	ControlledCharacter->attackComp->PlayerQuitSkill(SkillIndex);
}

void AProjectDPlayerController::ExecuteSkill(int32 SkillIndex)
{
	if(!ControlledCharacter) return;

	StopMovement();
	ControlledCharacter->attackComp->PlayerExecuteAttack(SkillIndex);
}


// <---------------------- Charging Skill ---------------------->

void AProjectDPlayerController::ChargingSkill(int32 SkillIndex)
{
	if(!ControlledCharacter) return;

	ControlledCharacter->attackComp->PlayerChargingSkill();
}

void AProjectDPlayerController::ChargingEndSkill(int32 SkillIndex)
{
	if(!ControlledCharacter) return;
    
	ControlledCharacter->attackComp->PlayerChargingEndSkill();
}

// <---------------------- Quest UI ---------------------->

void AProjectDPlayerController::QuestLogMenu()
{
	UWidgetQuestLog* QuestWidget = CreateWidget<UWidgetQuestLog>( GetWorld() , QuestLog_Widget );

	if(QuestWidget)
	{
		QuestWidget->AddToViewport(static_cast<uint32>(ViewPortPriority::Quest));
	}
}
