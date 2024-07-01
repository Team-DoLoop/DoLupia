// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/SpawnMonsterDamage.h"

#include "Components/WidgetComponent.h"
#include "Monsters/BossMonster.h"
#include "Monsters/Monster.h"
#include "Monsters/MonsterDamageWidget.h"

// Sets default values
ASpawnMonsterDamage::ASpawnMonsterDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	damageUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( "damageUI" ) );

	damageUI->SetupAttachment( RootComponent );
	damageUI->SetCastShadow( false );
}

// Called when the game starts or when spawned
void ASpawnMonsterDamage::BeginPlay()
{
	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ASpawnMonsterDamage::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	Super::BeginPlay();
	monsterDamageWidget = Cast<UMonsterDamageWidget>( damageUI->GetWidget() );
	
	AMonster* Monster = Cast<AMonster>( UGameplayStatics::GetActorOfClass( GetWorld() , AMonster::StaticClass() ) );

	monsterDamageWidget->SetDamage( 0 );

	FTimerHandle DelayTimerHandle;
	GetWorld()->GetTimerManager().SetTimer( DelayTimerHandle , FTimerDelegate::CreateLambda(
		[this]()->void
		{
			DestroyActor();
		}
	) , 2 , false );

	FFileHelper::SaveStringToFile( L"ASpawnMonsterDamage::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void ASpawnMonsterDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//HP Widget 빌보드 처리
	/*FVector camLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector dir = camLoc - damageUI->GetComponentLocation();
	dir.Normalize();
	damageUI->SetWorldRotation( dir.ToOrientationRotator() );*/

	
}

void ASpawnMonsterDamage::DestroyActor()
{
	this->Destroy();
}

