// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Trigger/TriggerBaseActor.h"
#include "NiagaraComponent.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gamemode/PlayerGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "World/Trigger/TriggerType.h"


// Sets default values
ATriggerBaseActor::ATriggerBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	triggerComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "triggerComp" ) );
	this->SetRootComponent( triggerComp );

	locationVFX = CreateDefaultSubobject<UNiagaraComponent>( TEXT( "locationVFX" ) );
	locationVFX->SetupAttachment( RootComponent );

	TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComp" ) );

	gm = nullptr;
	LvName = "";

	// Default TriggerType
	triggerType = EPlayerTriggerType::None;

}

// Called when the game starts or when spawned
void ATriggerBaseActor::BeginPlay()
{
	Super::BeginPlay();

	// FFileHelper 클래스를 이용하여 로그 파일 생성
	FString FilePath = FPaths::ProjectLogDir() + TEXT( "LogFileName.log" );
	FFileHelper::SaveStringToFile( L"ATriggerBaseActor::BeginPlay -> Start" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
		&IFileManager::Get() , ELogVerbosity::Log );

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	// 레벨 이동 트리거면 레벨 내에서 숨기기
	if (triggerType == EPlayerTriggerType::LevelTransition)
	{
		HideTrigger();
	}

	// 카메라 회전 트리거면 Timeline 적용, 시작할 때, NoColiision
	if (triggerType == EPlayerTriggerType::CameraAngle || CurveFloat)
	{
		triggerComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction( this , FName( "HandleTimelineProgress" ) );
		TimelineComp->AddInterpFloat( CurveFloat , ProgressFunction );

		FOnTimelineEvent TimelineFinishedFunction;
		TimelineFinishedFunction.BindUFunction( this , FName( "OnTimelineFinished" ) );
		TimelineComp->SetTimelineFinishedFunc( TimelineFinishedFunction );
	}

	FFileHelper::SaveStringToFile( L"ATriggerBaseActor::BeginPlay -> End" , *FilePath , FFileHelper::EEncodingOptions::AutoDetect ,
	&IFileManager::Get() , ELogVerbosity::Log );
}

// Called every frame
void ATriggerBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerBaseActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AProjectDCharacter* player = Cast<AProjectDCharacter>(OtherActor);

	// Player Overlap 일 때, 트리거 종류 별로 함수 실행
	if(player)
	{

		if (triggerType == EPlayerTriggerType::LevelTransition)
		{
			// 레벨 이동
			CallLevel( LvName , player );
		}
		else if (triggerType == EPlayerTriggerType::CameraAngle)
		{
			// 카메라 회전
			ChangeCameraAngle( 90.0f );
		}
		else if (triggerType == EPlayerTriggerType::CameraTargetArms)
		{
			ChangeCameraBooms( 500.0f );
		}
	}

}

void ATriggerBaseActor::CallLevel( FName Lvname , AProjectDCharacter* Character )
{
	gm->ChangeNextLv( Lvname, Character );
}

void ATriggerBaseActor::ChangeCameraAngle(float angle)
{
	// Player Load
	auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	if( player )
	{
		CameraBoom = player->GetCameraBoom();
		//FRotator NewRotation = player->GetCameraBoom()->GetRelativeRotation();
		//NewRotation.Yaw = angle;
		//player->GetCameraBoom()->SetRelativeRotation( NewRotation );

		// 초기 회전 값과 타겟 회전 값 설정
		InitialRotation = CameraBoom->GetRelativeRotation();
		TargetRotation = InitialRotation;
		TargetRotation.Yaw = angle;

		// 타임라인 초기화 및 시작
		TimelineComp->PlayFromStart();
	}
	
}

void ATriggerBaseActor::ChangeCameraBooms(float angle)
{
	// Player Load
	auto player = Cast<AProjectDCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld() , 0 ) );

	// 플레이어 쪽에서 카메라 설정값 셋팅하는 함수나, camera 변수 public 으로 바꿔줘야 겜모에서 변경 가능
	player->GetCameraBoom()->TargetArmLength = angle;
}

void ATriggerBaseActor::HandleTimelineProgress(float Value)
{
	if (CameraBoom)
	{
		FRotator NewRotation = FMath::Lerp( InitialRotation , TargetRotation , Value );
		CameraBoom->SetRelativeRotation( NewRotation );
	}
}

void ATriggerBaseActor::OnTimelineFinished()
{

}

void ATriggerBaseActor::ShowTrigger()
{
	locationVFX->SetVisibility( true );
	triggerComp->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
}

void ATriggerBaseActor::HideTrigger()
{
	locationVFX->SetVisibility( false );
	triggerComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void ATriggerBaseActor::ActiveTriggerCollision()
{
	if (triggerType == EPlayerTriggerType::CameraAngle)
	{
		triggerComp->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	}
	
}

