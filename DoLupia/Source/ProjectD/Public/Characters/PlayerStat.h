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
	UPROPERTY()
	int32 HP;

	UPROPERTY()
	int32 MP;

	UPROPERTY()
	float ATK;

	UPROPERTY()
	float DEF;
	
public:
	void initPlayerData();
	
	FORCEINLINE int32 GetHP() const {return HP;}
	FORCEINLINE void  SetHP(int32 _HP) {HP = _HP;}
	
	FORCEINLINE int32 GetMP() const {return MP;}
	FORCEINLINE void  SetMP(int32 _MP) {MP = _MP;}
	
	FORCEINLINE int32 GetATK() const {return ATK;}
	FORCEINLINE void  SetATK(float _ATK) {ATK = _ATK;}
	
	FORCEINLINE int32 GetDEF() const {return DEF;}
	FORCEINLINE void  SetDEF(float _DEF) {DEF = _DEF;}
};
