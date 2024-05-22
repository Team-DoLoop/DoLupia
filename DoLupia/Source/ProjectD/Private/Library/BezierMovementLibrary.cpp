// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/BezierMovementLibrary.h"

#include "World/Pickup.h"

void UBezierMovementLibrary::MoveObjectAlongCurve( UObject* WorldContextObject , AActor* Item , FVector StartPoint, FVector ActorSpeed, float GravityScale )
{
    if (!WorldContextObject || !Item)
        return;

    // 테스트용
    APickup* YourItem = Cast<APickup>( Item );
    if (YourItem)
    {
        YourItem->StartMovement( StartPoint, ActorSpeed );
    }

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint, ActorSpeed, GravityScale, 0.0f );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}

void UBezierMovementLibrary::UpdateObjectPosition(UObject* WorldContextObject, AActor* Item, FVector StartPoint, 
	FVector ActorSpeed, float GravityScale, float Time)
{
    if (!WorldContextObject || !Item)
        return;


    const float Gravity = 980.0f; // 중력 가속도 (cm/s²)
    const float Radians = FMath::DegreesToRadians( 45.0 );

    // 시간에 따른 x와 y 좌표 계산
    const float X = ActorSpeed.X * Time * FMath::Cos( Radians );
    const float Y = ActorSpeed.Y * Time * FMath::Sin( Radians ) -GravityScale * Gravity * Time * Time;
    const float Z = ActorSpeed.Z * Time * FMath::Cos( Radians );

    const FVector& NewPosition = FVector( StartPoint.X + X, (float)StartPoint.Y + Z, StartPoint.Z + Y);

    Item->SetActorLocation( NewPosition );

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint, 
		ActorSpeed, GravityScale, Time + WorldContextObject->GetWorld()->GetDeltaSeconds() );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}