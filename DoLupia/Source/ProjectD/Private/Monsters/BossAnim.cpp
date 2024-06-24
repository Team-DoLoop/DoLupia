// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossAnim.h"

#include "Characters/ProjectDCharacter.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"
#include "Monsters/BossMonster.h"

void UBossAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	bIsAttackComplete = true;

	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	Boss = Cast<ABossMonster>( UGameplayStatics::GetActorOfClass( GetWorld() , ABossMonster::StaticClass() ) );
}


void UBossAnim::NativeUpdateAnimation( float DeltaSeconds )
{
	Super::NativeUpdateAnimation( DeltaSeconds );

	Boss = Cast<ABossMonster>( UGameplayStatics::GetActorOfClass( GetWorld() , ABossMonster::StaticClass() ) );

}
//===============Delay_Launch=======================

void UBossAnim::EndLaunchAnimation()
{
	Boss->IsLaunching = false;
	bFinishDelay = true;

}
//===============Delay_LookAround=======================

void UBossAnim::EndLookAroundAnimation()
{
	bFinishDelay = true;
}


//===============Hit Attack=======================

void UBossAnim::OnDoHitAttackAnimation()
{
	FVector Start = Boss->GetActorLocation();
	FVector End = Start + (Boss->GetActorForwardVector() * 800.f);

	FCollisionShape CollisionShape = FCollisionShape::MakeSphere( 400.0f );
	FHitResult HitResult;

	bool bHit = GetWorld()->SweepSingleByChannel(
		HitResult ,
		Start ,
		End ,
		FQuat::Identity ,
		ECC_Pawn ,
		CollisionShape
	);

	//DrawDebugSphere( GetWorld() , Start , CollisionShape.GetSphereRadius() , 12 , FColor::Red , false , 1.0f );
	//DrawDebugSphere( GetWorld() , End , CollisionShape.GetSphereRadius() , 12 , FColor::Red , false , 1.0f );
	//DrawDebugLine( GetWorld() , Start , End , FColor::Green , false , 1.0f , 0 , 1.0f );

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			AProjectDCharacter* player = Cast<AProjectDCharacter>( UGameplayStatics::GetActorOfClass( GetWorld() , AProjectDCharacter::StaticClass() ) );
			player->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 100 );

		}
	}

}


void UBossAnim::OnEndHitAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Hit애니메이션 끝, 브로드캐스트 호츌" ) );

}




//===============Fire Attack=======================

void UBossAnim::OnDoFireAttackAnimation()
{
	FVector Start = Boss->GetActorLocation(); // 위치 집게로 바꿔
	FVector ForwardVector = Boss->GetActorForwardVector(); // 집게의 앞 방향으로
	FVector End = ((ForwardVector * 200.f) + Start);
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;


	//==============effect visible로 바꿔라!!==============

	bool bHit = GetWorld()->LineTraceSingleByChannel( HitResult , Start , End , ECC_Visibility , CollisionParams );

	if (bHit)
	{
		// HitResult에 포함된 액터에 대한 데미지 처리
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			AProjectDCharacter* player = Cast<AProjectDCharacter>( UGameplayStatics::GetActorOfClass( GetWorld() , AProjectDCharacter::StaticClass() ) );
			player->TakeHit( EAttackType::BASIC , EEffectAttackType::NONE , 100 );
		}
	}
}

void UBossAnim::OnEndFireAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Fire애니메이션 끝, 브로드캐스트 호츌" ) );

}

//===============Grab Attack=======================
void UBossAnim::OnDoGrabAttackAnimation()
{
	Boss->IsShieldActive = true;
}


void UBossAnim::OnEndGrabAttackAnimation()
{
	Boss->ThrowAttack();

}

void UBossAnim::OnEndThrowAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	Boss->IsShieldActive = false;
	OnEndAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Grab애니메이션 끝, 브로드캐스트 호츌" ) );

}


//===============BlastFireAttack=======================
void UBossAnim::OnDoBlastFireAttackAnimation()
{
	auto AIlib = gm->GetAIConnectionLibrary();
	AIlib->SendBImgToSrv( 1 ); //상태이상 : 화염
}

void UBossAnim::OnEndBlastFireAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndAttack.Broadcast();
}



//===============BlastLighteningAttack=================
void UBossAnim::OnDoBlastLighteningAttackAnimation()
{
	auto AIlib = gm->GetAIConnectionLibrary();
	AIlib->SendBImgToSrv( 2 ); //상태이상  : 독
}

void UBossAnim::OnEndBlastLighteningAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndAttack.Broadcast();
}

//=======================DIe==============================
void UBossAnim::OnEndDieAnimation()
{
	Boss->DestroyMonster();

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle ,
		[this]() {
			gm->PlayOutroSequencer();
		} ,
		0.5f , // 지연 시간(초)
		false
	);

	//gm->PlayOutroSequencer();
}
