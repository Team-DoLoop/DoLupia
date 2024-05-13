// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Monster.h"
#include "Monsters/MonsterFSM.h"
#include "Monsters/MonsterHPWidget.h"
#include "Monsters/DamageTestActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "Characters/ProjectDCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Monsters/MonsterAnim.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>MonsterMesh(TEXT("/Game/Monsters/Assets/Ancient_Golem/Mesh/SK_Ancient_Golem.SK_Ancient_Golem"));
	RootComponent->SetWorldScale3D(FVector(1.5f));
	if (MonsterMesh.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MonsterMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -189), FRotator(0, -90, 0));
	}

	FName WheelsSocket( TEXT( "WheelsSocket" ) );
	if (GetMesh()->DoesSocketExist( WheelsSocket ))
	{
		Wheels = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "Wheels" ) );
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WHEELS( TEXT( "/Game/Monsters/Assets/Ancient_Golem/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels"  ));
		if (SK_WHEELS.Succeeded())
		{
			Wheels->SetSkeletalMesh( SK_WHEELS.Object );
		}
		Wheels->SetupAttachment( GetMesh() , WheelsSocket );
	}

	

	MonsterFSM = CreateDefaultSubobject<UMonsterFSM>(TEXT("MonsterFSM"));

	healthUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( "healthUI" ) );

	healthUI->SetupAttachment( RootComponent );
	healthUI->SetCastShadow( false );

	
	

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	int yaw = rand() % 360;
	SetActorRotation( FRotator( 0 , yaw ,0 ) );
	monsterHPWidget = Cast<UMonsterHPWidget>( healthUI->GetWidget() );
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this , &AMonster::OnMyCompBeginOverlap );

	anim = Cast<UMonsterAnim>( this->GetMesh()->GetAnimInstance() );

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//HP Widget 빌보드 처리
	FVector camLoc = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
	FVector dir = camLoc - healthUI->GetComponentLocation();
	dir.Normalize();
	healthUI->SetWorldRotation( dir.ToOrientationRotator() );

	//항상 플레이어를 바라보도록 회전
	FVector rot = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - this->GetActorLocation();
	rot.Normalize();
	if(bHasTarget)
	{
		this->SetActorRotation( rot.ToOrientationRotator() );
	}
}


void AMonster::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//공격 받을 시 OnMyTakeDamage() 호출
	if(AProjectDCharacter* testActor = Cast<AProjectDCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::OnMyCompBeginOverlap" ) );

		OnMyTakeDamage(10);
	}
}


void AMonster::PatrolState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::PatrolState()" ) );
	//애니메이션 상태 업데이트
	anim->animState = MonsterFSM->state;

	//플레이어를 타겟으로 설정
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();
	if (TargetVector.Size() < TargetRange) {
		MonsterFSM->state = EMonsterState::Move;
		anim->animState = MonsterFSM->state;
		bHasTarget = true;
	}
}

void AMonster::MoveState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( " AMonster::MoveState()" ) );
	//플레이어 방향으로 이동
	MoveToTarget();

	if (TargetVector.Size() < AttackRange) {
		MonsterFSM->state = EMonsterState::Attack;
		anim->animState = MonsterFSM->state;
		anim->bAttackDelay = true;
		currentTime = attackDelayTime;
	}
}

void AMonster::AttackState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::AttackState()" ) );
	currentTime += GetWorld()->GetDeltaSeconds();
	TargetVector = target->GetActorLocation() - this->GetActorLocation();

	if(currentTime>attackDelayTime)
	{
		currentTime = 0;
		anim->bAttackDelay = true;
		bOnceAttack = true;
	}

	if(bOnceAttack)
	{
		if (TargetVector.Size() > AttackRange) {
			MonsterFSM->state = EMonsterState::Move;
			anim->animState = MonsterFSM->state;
			bOnceAttack = false;
		}
	}

}

void AMonster::DamageState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::DamageState()" ) );

	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 1.5)
	{
		MonsterFSM->state = EMonsterState::Move;
		this->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
		currentTime = 0;
		anim->animState = MonsterFSM->state;
	}

}

void AMonster::DieState()
{
	//GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::DieState()" ) );

	anim->animState = MonsterFSM->state;

	this->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	//죽음 애니메이션 끝난 후 destroy
	currentTime += GetWorld()->GetDeltaSeconds();
	if (currentTime > 4)
	{
		//아이템 드랍

		this->Destroy();
		currentTime = 0;
	}
}

void AMonster::MoveToTarget()
{
	TargetVector = target->GetActorLocation() - this->GetActorLocation();
	this->AddMovementInput( TargetVector.GetSafeNormal() );

	FRotator MonsterRotation = FRotationMatrix::MakeFromX( TargetVector ).Rotator();
	this->SetActorRotation( MonsterRotation );

}

void AMonster::OnMyTakeDamage(int damage)
{
	currentHP -= damage;
	monsterHPWidget->SetHP( currentHP , maxHP );
	this->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	if (currentHP < 0)
	{
		currentHP = 0;
	}

	if (currentHP > 0)
	{
		MonsterFSM->state = EMonsterState::Damage;
	}

	else
	{
		MonsterFSM->state = EMonsterState::Die;
	}
	anim->animState = MonsterFSM->state;
	// 충돌체 끄기
	this->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

