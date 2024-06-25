// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/StatusEffectComp.h"

// Sets default values for this component's properties
UStatusEffectComp::UStatusEffectComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusEffectComp::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"UStatusEffectComp::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
	// ...
	
}


// Called every frame
void UStatusEffectComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusEffectComp::SetStatusEffect(EEffectAttackType _statusEffect)
{
	// 어떤 StatusEffect인지에 따라
	// Damage, IsDotAttack, VFX, SFX 설정
	switch (_statusEffect)
	{
	case EEffectAttackType::NONE : break;
	case EEffectAttackType::BLEED : BleedingStatusEffect(); break;
	case EEffectAttackType::POISON : PoisonStatusEffect(); break;
	}

	// AddStatusEffect();
}

void UStatusEffectComp::AddStatusEffect(ACharacter* Target)
{
	// 설정한 값들 Target에 적용
}

void UStatusEffectComp::BleedingStatusEffect()
{
	statusEffectType = EEffectAttackType::BLEED;
}

void UStatusEffectComp::PoisonStatusEffect()
{
	statusEffectType = EEffectAttackType::POISON;
}


