// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "PlayerAttackComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerAttackComp : public UActorComponent
{
	GENERATED_BODY()
	
	friend class AProjectDPlayerController;
	
public:	
	// Sets default values for this component's properties
	UPlayerAttackComp();

private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;
	
	UPROPERTY()
	class UPlayerFSMComp* PlayerFSMComp;

	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnim;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	// <---------------------- Player ---------------------->
private:

public:
	void TurnPlayer();

	

	// <---------------------- Attack ---------------------->
private:
	UPROPERTY()
	TArray<class UPlayerSkillBase*> PlayerSkills;

protected:
	void Attack();
	
public:
	void AttackEnd();
	void PlayerExecuteSkill(int32 SkillIndex);

	FORCEINLINE class TArray<class UPlayerSkillBase*> GetPlayerSkills() const {return PlayerSkills;}


};
