// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Skill/PlayerSkillBase.h"
#include "PlayerSkillShield.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTD_API APlayerSkillShield : public APlayerSkillBase
{
	GENERATED_BODY()

public:
	APlayerSkillShield();

protected:
	virtual void BeginPlay() override;
	virtual void ActivateSkill() override;
	

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
private:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;
};
