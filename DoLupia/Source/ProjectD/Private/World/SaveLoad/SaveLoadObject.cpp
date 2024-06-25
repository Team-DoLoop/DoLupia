﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SaveLoad/SaveLoadObject.h"

#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Library/GameSaveManager.h"
#include "Library/LevelManager.h"

// Sets default values
ASaveLoadObject::ASaveLoadObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveLoadObject::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ASaveLoadObject::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void ASaveLoadObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Trigger)
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName( GetWorld() );

		// 레벨 이름이 "Tutorial"인지 확인
		if (!CurrentLevelName.Equals( TEXT( "Tutorial" ) , ESearchCase::IgnoreCase ) && !CurrentLevelName.Equals( TEXT( "Opening" ) , ESearchCase::IgnoreCase ))
			LOAD( ESaveType::SAVE_MAIN , "PlayerMainSave" , true , false , false )
		else
		{
			LOAD( ESaveType::SAVE_1 , "TutorialSave" , false , false , false );
			APlayerGameMode* gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
			gm->StartGameStory();
		}
			




		Destroy();
		return;
	}

	Trigger = true;
}

