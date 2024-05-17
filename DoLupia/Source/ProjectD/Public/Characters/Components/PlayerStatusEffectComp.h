// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/StatusEffectComp.h"
#include "PlayerStatusEffectComp.generated.h"

/**
 * 장착 무기에 따라 공격에 상태이상을 적용
 * VFX : 무기 이펙트
 */
UCLASS()
class PROJECTD_API UPlayerStatusEffectComp : public UStatusEffectComp
{
	GENERATED_BODY()

public:
	UPlayerStatusEffectComp();

protected:

public:
	virtual void SetStatusEffect(EStatusEffectType _statusEffect) override;

	virtual void AddStatusEffect(ACharacter* Target) override;

};
