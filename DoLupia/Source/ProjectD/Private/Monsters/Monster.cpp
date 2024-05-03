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

	MonsterFSM = CreateDefaultSubobject<UMonsterFSM>(TEXT("MonsterFSM"));

	healthUI = CreateDefaultSubobject<UWidgetComponent>( TEXT( "healthUI" ) );

	healthUI->SetupAttachment( RootComponent );
	//healthUI->SetRelativeLocation( FVector( 0 , 0 , 100 ) );

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	int yaw = rand() % 360;
	SetActorRotation( FRotator( 0 , yaw ,0 ) );
	monsterHPWidget = Cast<UMonsterHPWidget>( healthUI->GetWidget() );

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic( this , &AMonster::OnMyCompBeginOverlap );
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
}


void AMonster::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ADamageTestActor* testActor = Cast<ADamageTestActor>( OtherActor )
	//공격 받을 시 OnMyTakeDamage() 호출
	if(AProjectDCharacter* testActor = Cast<AProjectDCharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage( -1 , 5.f , FColor::Green , TEXT( "AMonster::OnMyCompBeginOverlap" ) );

		OnMyTakeDamage(10);
	}
}


void AMonster::OnMyTakeDamage(int damage)
{
	currentHP -= damage;
	MonsterFSM->TakeDamage();
	monsterHPWidget->SetHP( currentHP , maxHP );
}

