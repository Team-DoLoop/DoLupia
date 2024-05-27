// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Common/UseColor.h"
#include "Components/ActorComponent.h"
#include "Interfaces/SkillInterface.h"
#include "PlayerAttackComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTD_API UPlayerAttackComp : public UActorComponent, public ISkillInterface
{
	GENERATED_BODY()
	
	friend class AProjectDPlayerController;
	
public:	
	// Sets default values for this component's properties
	UPlayerAttackComp();

private:
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	// <---------------------- Player ---------------------->
private:
	UPROPERTY()
	class AProjectDCharacter* Player;

	UPROPERTY()
	class AProjectDPlayerController* PlayerController;
	
	UPROPERTY()
	class UPlayerFSMComp* PlayerFSMComp;

	UPROPERTY()
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY()
	class APlayerStat* PlayerStat;

	
public:


	

	// <---------------------- Attack ---------------------->
private:
	int32 PlayerMaxMP;
	
	float MPRegenRate;
	float MPRegenTime;
	float CurrentRegenTime;

	int PlayerAttackStatus = 0;
	EUseColor CurrentSkillColor = EUseColor::NONE; // X, 빨, 노, 파
	
	UPROPERTY()
	TArray<class UPlayerSkillBase*> PlayerSkills;

protected:
	void Attack();
	
public:
	virtual void CancelSkill() override;
	virtual void ReadySkill() override;
	virtual void CompleteSkill() override;
	
	void PlayerExecuteSkill(int32 SkillIndex);

	FORCEINLINE class TArray<class UPlayerSkillBase*> GetPlayerSkills() const {return PlayerSkills;}


};
