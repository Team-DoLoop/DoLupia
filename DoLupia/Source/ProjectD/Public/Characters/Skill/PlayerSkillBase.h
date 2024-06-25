// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerSkillBase.generated.h"

UCLASS()
class PROJECTD_API APlayerSkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ActivateSkill();
	virtual void SkillCameraShake(TSubclassOf<UCameraShakeBase> _CSSkill);

	float SkillVolume;
	int32 SkillDamage;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bIsShowDebugLine;
	FORCEINLINE void SetSkillDamage(int32 _SkillDamage){SkillDamage = _SkillDamage;}
	
	UPROPERTY(EditAnywhere, Category = Skill_Camera)
	TSubclassOf<UCameraShakeBase> CSSkill;										// Camera Shake

private:
	
	
};
