// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterSword.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMonsterSword::AMonsterSword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AMonsterSword::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"AMonsterSword::BeginPlay -> Start End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void AMonsterSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterSword::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//공격 판정
}

