// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillWaterBlade.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerSkillWaterBlade : public APlayerSkillBase
{
	GENERATED_BODY()

public:
	APlayerSkillWaterBlade();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void ActivateSkill() override;
	
	FORCEINLINE void SetSkillDamage(int32 _SkillDamage){SkillDamage = _SkillDamage;}
	FORCEINLINE void SetSkillDirection(FVector _Direction){Direction = _Direction;}
	FORCEINLINE void SetSkillRot(FRotator _Rot){Rot = _Rot;}

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
private:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComp;
	
	UPROPERTY(EditAnywhere, Category = "Damage")
	int32 SkillDamage;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed = 1000.0f;
	
	FVector Direction;
	FRotator Rot;
};
