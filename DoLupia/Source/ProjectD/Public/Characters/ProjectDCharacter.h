// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/DamageInterface.h"
#include "Interfaces/InteractionInterface.h"
#include "Quest/QuestInteractionInterface.h"
#include "ProjectDCharacter.generated.h"

class UPlayerTutorialComp;
class UNPCInteractionWidget;
class ADoLupiaHUD;
class UPlayerDefaultsWidget;
class UItemBase;
class UInventoryComponent;
class UTimelineComponent;
class UQuestLogComponent;
class UQuestInventoryComponent;
class UPlayerBattleWidget;
class ATestNPCCharacter;
class ANPCBase;

/*/Minimap
class UDialogueTree;
class UMapViewComponent;
class UMapIconComponent;
class UMapFogRevealerComponent;*/

enum class EAttackType : uint8;
enum class EEffectAttackType : uint8;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCehckTime(0.0f) { };

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCehckTime;
	
};

// Delegate 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnObjectiveIDCalled , FString , ObjectiveID , int32 , Value = 1);


UCLASS(Blueprintable)
class AProjectDCharacter : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

	friend class AProjectDPlayerController;
private:
	
protected:
	virtual void BeginPlay() override;

public:
	AProjectDCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	
	// <---------------------- Camera ---------------------->
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class USpringArmComponent* CameraBoom;
	
protected:
	
public:

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	
	// <---------------------- Player ---------------------->
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	class UPlayerFSMComp* PlayerFSM;

	UPROPERTY(VisibleAnywhere)
	class UGadgetComponent* Gadget;

	UPROPERTY(VisibleAnywhere)
	class APlayerStat* PlayerStat;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraComp;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;

	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnim;

	int32 PlayerMaxHP;

protected:
	
public:
	FORCEINLINE class UPlayerFSMComp* GetPlayerFSMComp() const {return PlayerFSM;}
	FORCEINLINE APlayerStat* GetPlayerStat() const { return PlayerStat; }
	FORCEINLINE class UGadgetComponent* GetGadgetComp() const {return Gadget;}
	FORCEINLINE UPlayerAnimInstance* GetPlayerAnim() const { return PlayerAnim; }
	FORCEINLINE class UNiagaraComponent* GetNiagaraComp()const {return NiagaraComp;}

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void TurnPlayer();

	

	// <---------------------- UI ---------------------->
private:
	UPROPERTY()
	ADoLupiaHUD* HUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerDefaultsWidget> PlayerDefaultsWidgetFactory;

	UPROPERTY()
	UPlayerDefaultsWidget* PlayerDefaultsWidget;

	UPROPERTY()
	class UPlayerBattleWidget* PlayerBattleWidget;

public:
	UPlayerDefaultsWidget* GetPlayerDefaultsWidget() const { return PlayerDefaultsWidget; }
	void UseQuickSlot( int32 SlotNumber );

	ADoLupiaHUD* GetDoLupiaHUD() { return HUD; }

	UPlayerBattleWidget* GetPlayerBattleWidget() const { return PlayerBattleWidget; }

	void OnSystemCall( const FText& Message ) const;
	void OnSystemCallSoundCue( const FText& Message, class USoundCue* SoundCue) const;
	void OnSystemCallSoundWave(const FText& Message , class USoundWave* SoundWave ) const;

protected:
	void ToggleMenu();

private:
	void HoveredQuickSlot();
	bool PossibleChangeGameMode();


	
	// <---------------------- Cape ---------------------->
private:
	UPROPERTY(VisibleAnywhere, Category = "Child")
	class UChildActorComponent* CapeComp;

	
	// <---------------------- Move ---------------------->
private:
	UPROPERTY(EditDefaultsOnly)
	class UPlayerMoveComp* moveComp;

protected:

public:
	FORCEINLINE class UPlayerMoveComp* GetPlayerMoveComp() const {return moveComp;}
	
	
	// <---------------------- Attack ---------------------->
private:
	UPROPERTY(EditDefaultsOnly)
	class UPlayerAttackComp* attackComp;
	
	// 타일라인 변수들 카메라 이동 변수 -> 특수 스킬 사용 시 줌인 기능
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector DefaultCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector AimingCameraLocation;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> AimingCameraTimeline;

	UPROPERTY(EditDefaultsOnly,  Category = "Character | Aim Timeline")
	UCurveFloat* AimingCameraCurve;

	bool bIsAiming;

protected:
	void Aim();
	void StopAiming();
	UFUNCTION()
	void UpdateCameraTimeline(const float TimelineValue) const;
	UFUNCTION()
	void CameraTimelineEnd();

public:
	FORCEINLINE class UPlayerAttackComp* GetAttackComp() const {return attackComp;}
	void TakeHit(EAttackType AttackType, EEffectAttackType EffectAttackType, float Damage);
	virtual void TakeDamage( float Damage ) override;
	void LyingEnd();

	

	// <---------------------- Effect Attack Hit ---------------------->
private:
	FTimerHandle EffectTimerHandle;
	
	UPROPERTY(VisibleAnywhere, Category = "Effect Attack Hit")
	float FireEffectTime = 5.0f;

	UPROPERTY(VisibleAnywhere, Category = "Effect Attack Hit")
	float ElecEffectTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Character | Effect Attack Hit")
	class UNiagaraSystem* FireNS;

	UPROPERTY(EditAnywhere, Category = "Character | Effect Attack Hit")
	class UNiagaraSystem* ElecNS;

	UNiagaraSystem* EffectNS;

public:

	void TakeEffectAttackHit(EEffectAttackType EffectAttackType);
	void TakeEffectAttackHitEnd();


	
	// <---------------------- Interaction ---------------------->
private:
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<class IInteractionInterface> TargetInteractable;

	// 인터렉션 변수들
	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractionData;

protected:
	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractionableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();
	
public:
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }

	
	
	// <---------------------- Item ---------------------->
public:
	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);
	void UpdateInteractionWidget() const;
	class UItemBase* SwitchEquipItem(UItemBase* ItemBase);
	

	// <---------------------- Inventory ---------------------->	
private:
	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	UInventoryComponent* PlayerInventory;
	
protected:

public:
	FORCEINLINE UInventoryComponent* GetInventory() const { return PlayerInventory; };
	

	// <---------------------- Quest ---------------------->
private:
	UPROPERTY(VisibleAnywhere, Category = "Character | Quest")
	UQuestLogComponent* PlayerQuest;

	//테스트용 인벤토리 컴포넌트 추가!
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	UQuestInventoryComponent* PlayerQuestInventory;
	
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	TScriptInterface<class IQuestInteractionInterface> QuestInteractable;
	
	// Quest 변수
	UPROPERTY()
	AActor* LookAtActor;

	UPROPERTY()
	ANPCBase* SpecificActor;
	
protected:

	void PerformTrace();

	UPROPERTY( EditAnywhere )
	float TraceDistance = 2000.0f;  // 트레이스 거리 설정

	AActor* LastHitActor;  // 마지막으로 히트된 액터를 저장

	/*
	UPROPERTY( EditAnywhere )
	TSubclassOf<UNPCInteractionWidget> NPCInteractWidget;

	UPROPERTY()
	UNPCInteractionWidget* NPCInteractGWidget;
	*/
	
public:	
	FORCEINLINE UQuestLogComponent* GetQuestLogComponent() const { return PlayerQuest; };

	FORCEINLINE UQuestInventoryComponent* GetQuestInventoryComponent() const { return PlayerQuestInventory; };
	
	// Event Dispatcher 선언
	UPROPERTY( BlueprintAssignable , Category = "Events" )
	FOnObjectiveIDCalled OnObjectiveIDCalled;

	/*UPROPERTY(BlueprintAssignable , Category = "Events")
	FOnQuestIDCalled OnQuestIDCalled;
	*/


	/* Quest Decline 기능 삭제
	// <---------------------- Dialog ---------------------->
	void EnableDialogue();
	void DisableDialogue();
	bool IsDialogueEnabled() const;

private:
	bool bIsDialogueEnabled;
	*/


	
	// <---------------------- Tutorial ---------------------->
private:
	UPROPERTY(VisibleAnywhere, Category = "Character | Tutorial")
	UPlayerTutorialComp* TutorialComp;
	
public:
	FORCEINLINE UPlayerTutorialComp* GetTutorialComp() const { return TutorialComp; };


	// <-------------------- MiniMap ---------------------->
private:
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class UMapViewComponent* MapView;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class UMapIconComponent* MapIcon;
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = Camera , meta = (AllowPrivateAccess = "true") )
	class UMapRevealerComponent* MapRevealer;
};

