// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractionInterface.h"
#include "Quest/QuestInteractionInterface.h"
#include "ProjectDCharacter.generated.h"

class ADoLupiaHUD;
class UInventoryComponent;
class UItemBase;
class UTimelineComponent;
class UQuestLogComponent;

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnObjectiveIDCalled , FString, ObjectiveID);


UCLASS(Blueprintable)
class AProjectDCharacter : public ACharacter
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:
	
public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	
	
	// <---------------------- Player State ---------------------->
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, meta = (AllowPrivateAccess = "true"))
	class UPlayerFSMComp* PlayerFSM;

protected:
	
public:

	

	// <---------------------- UI ---------------------->
private:
	UPROPERTY()
	ADoLupiaHUD* HUD;
	
protected:
	void ToggleMenu();

public:

	
	
	// <---------------------- Attack ---------------------->
private:
	UPROPERTY(EditDefaultsOnly)
	class UPlayerAttackComp* attackComp;
	
	// 타일라인 변수들 카메라 이동 변수 -> 특수 스킬 사용 시 줌인 기능
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector DefaultCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector AimingCameraLocation;

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
private:
	
protected:

public:
	void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);
	void UpdateInteractionWidget() const;

	

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
	
	UPROPERTY( VisibleAnywhere , Category = "Character | Quest" )
	TScriptInterface<class IQuestInteractionInterface> QuestInteractable;
	
	// Quest 변수
	UPROPERTY()
	AActor* LookAtActor;
	
protected:
	
public:	
	FORCEINLINE UQuestLogComponent* GetQuestLogComponent() const { return PlayerQuest; };
	
	// Event Dispatcher 선언
	UPROPERTY( BlueprintAssignable , Category = "Events" )
	FOnObjectiveIDCalled OnObjectiveIDCalled;
	
};

