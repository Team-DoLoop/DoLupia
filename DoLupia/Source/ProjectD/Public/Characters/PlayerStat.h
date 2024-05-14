// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStat.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTD_API APlayerStat : public APlayerState
{
	GENERATED_BODY()

	APlayerStat();
	
private:

protected:
	UPROPERTY(VisibleAnywhere)
	int32 MaxHP;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHP;

	UPROPERTY(VisibleAnywhere)
	int32 MaxMP;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentMP;

	UPROPERTY(VisibleAnywhere)
	float ATK;

	UPROPERTY(VisibleAnywhere)
	float DEF;
	
public:
	void initPlayerData();
	
	FORCEINLINE int32 GetHP() const {return CurrentHP; }
	FORCEINLINE void  SetHP(int32 _HP)
	{
		int32 NewHP = CurrentHP + _HP;

		if(NewHP > MaxHP)
			NewHP = MaxHP;

		CurrentHP = NewHP;
	}
	
	FORCEINLINE int32 GetMP() const {return CurrentHP;}
	FORCEINLINE void  SetMP(int32 _MP)
	{
		int32 NewMP = CurrentMP + _MP;

		if (NewMP > MaxMP)
			NewMP = MaxMP;

		CurrentMP = NewMP;
	}

	
	FORCEINLINE int32 GetATK() const {return ATK;}
	FORCEINLINE void  SetATK(float _ATK) {ATK = _ATK;}
	
	FORCEINLINE int32 GetDEF() const {return DEF;}
	FORCEINLINE void  SetDEF(float _DEF) {DEF = _DEF;}
};
