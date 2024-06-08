// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/BezierMovementLibrary.h"

#include "Components/SphereComponent.h"
#include "World/Pickup.h"

void UBezierMovementLibrary::MoveObjectAlongCurve( UObject* WorldContextObject , AActor* Item , FVector StartPoint, 
	FVector ActorSpeed, float GravityScale )
{
    if (!WorldContextObject || !Item)
        return;

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint, ActorSpeed, GravityScale, 0.0f );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}

FVector UBezierMovementLibrary::VectorSeed(AActor* ContextActor)
{
	if(!ContextActor)
	{
        return FVector
        (
            FMath::RandRange( -500 , -300 ) ,
            FMath::RandRange( 300 , 500 ) ,
            FMath::RandRange( -500 , -300 )
        );
	}

    FVector StartPosition = ContextActor->GetActorLocation();
    FVector StartRotation = ContextActor->GetActorRotation().Vector();

    // 위치와 회전 값을 XOR 연산하여 고유한 시드 값 생성
    // 나중에 확률 추가하려면 따로 구현 해야함.
    uint32 Seed = StartPosition.X;
    Seed = Seed ^ (uint32)StartPosition.Y;
    Seed = Seed ^ (uint32)StartPosition.Z;
    Seed = Seed ^ (uint32)StartRotation.X;
    Seed = Seed ^ (uint32)StartRotation.Z;
    Seed = Seed ^ (uint32)StartRotation.Y;

    FRandomStream RandomStream( Seed );

    int32 minus = FMath::RandRange(0, 3);

    if(minus == 0)
    {
        return FVector
        (
            RandomStream.RandRange( -500 , -300 ) ,
            RandomStream.RandRange( 300 , 500 ) ,
            RandomStream.RandRange( -500 , -300 )
        );
    }
    else if(minus == 1)
    {
        return FVector
        (
            RandomStream.RandRange( -500 , -300 ) ,
            RandomStream.RandRange( 300 , 500 ) ,
            RandomStream.RandRange( 300 , 500 )
        );
    }
    else if (minus == 2)
    {
        return FVector
        (
            RandomStream.RandRange( 300 , 500 ) ,
            RandomStream.RandRange( 300 , 500 ) ,
            RandomStream.RandRange( -500 , -300 )
        );
    }

    return FVector
    (
        RandomStream.RandRange( 300 , 500 ) ,
        RandomStream.RandRange( 300 , 500 ) ,
        RandomStream.RandRange( 300 , 500 )
    );

}

void UBezierMovementLibrary::UpdateObjectPosition(UObject* WorldContextObject, AActor* Item, FVector StartPoint, 
                                                  FVector ActorSpeed, float GravityScale, float Time)
{
    if (!WorldContextObject || !Item)
        return;

    TArray<USphereComponent*> SphereComponents;
    Item->GetComponents<USphereComponent>( SphereComponents );

    if(SphereComponents.Num() > 0)
    {
	    if(SphereComponents[0]->GetCollisionEnabled() == ECollisionEnabled::QueryAndPhysics)
			return;
    }

    const float Gravity = 980.0f; // 중력 가속도 (cm/s²)
    const float Radians = FMath::DegreesToRadians( 45.0 );

    // 시간에 따른 x와 y 좌표 계산
    const float X = ActorSpeed.X * Time * FMath::Cos( Radians );
    const float Y = ActorSpeed.Y * Time * FMath::Sin( Radians ) -GravityScale * Gravity * Time * Time; //  
    const float Z = ActorSpeed.Z * Time * FMath::Cos( Radians );

    const FVector& NewPosition = FVector( StartPoint.X + X, (float)StartPoint.Y + Z, StartPoint.Z + Y);

    Item->SetActorLocation( NewPosition );

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint, 
		ActorSpeed, GravityScale, Time + WorldContextObject->GetWorld()->GetDeltaSeconds() );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}
