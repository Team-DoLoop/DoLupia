// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BossAnim.h"
#include "Monsters/BossMonster.h"

void UBossAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	bIsAttackComplete = true;
}

void UBossAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Boss = Cast<ABossMonster>( UGameplayStatics::GetActorOfClass( GetWorld() , ABossMonster::StaticClass() ) );
	
}

void UBossAnim::OnEndHitAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndHitAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Hit애니메이션 끝, 브로드캐스트 호츌" ) );

}

void UBossAnim::OnEndFireAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndFireAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Fire애니메이션 끝, 브로드캐스트 호츌" ) );

}

void UBossAnim::OnEndGrabAttackAnimation()
{
	bAttackDelay = false;
	bIsAttackComplete = true;
	Boss->IsDelaying = true;
	OnEndGrabAttack.Broadcast();
	UE_LOG( LogTemp , Warning , TEXT( "UBossAnim:: Grab애니메이션 끝, 브로드캐스트 호츌" ) );

}
