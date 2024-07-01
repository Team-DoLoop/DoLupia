// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Sword/LongSword.h"

ALongSword::ALongSword()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALongSword::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALongSword::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ALongSword::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}
