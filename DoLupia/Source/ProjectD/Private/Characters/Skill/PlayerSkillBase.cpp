// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skill/PlayerSkillBase.h"

#include "Characters/ProjectDCharacter.h"
#include "Characters/Components/PlayerAttackComp.h"

// Sets default values
APlayerSkillBase::APlayerSkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSkillBase::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"APlayerSkillBase::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	auto Player = Cast<AProjectDCharacter>( GetWorld()->GetFirstPlayerController()->GetCharacter() );
	if(Player)
	{
		bIsShowDebugLine = Player->GetbIsShowDebugLine();
		if(auto attackComp =  Player->GetAttackComp())
		{
			SkillVolume = attackComp->GetSkillVolume();
		}
	}
	else
	{
		FFileHelper::SaveStringToFile( L"APlayerSkillBase::BeginPlay -> Player nullptr" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
			&IFileManager::Get() , ELogVerbosity::Log );
	}
}

void APlayerSkillBase::ActivateSkill()
{
	// 카메라 흔들기
	if(CSSkill) SkillCameraShake(CSSkill);
}

void APlayerSkillBase::SkillCameraShake(TSubclassOf<UCameraShakeBase> _CSSkill)
{
	if(!_CSSkill) return;
	
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(_CSSkill, 1.0f);
}

// Called every frame
void APlayerSkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

