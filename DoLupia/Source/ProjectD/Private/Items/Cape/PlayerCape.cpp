// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Cape/PlayerCape.h"

// Sets default values
APlayerCape::APlayerCape() : AAITxtHandlerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APlayerCape::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"APlayerCape::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
	
}

// Called every frame
void APlayerCape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

