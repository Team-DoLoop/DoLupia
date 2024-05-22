// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/BezierMovementLibrary.h"

#include "World/Pickup.h"

void UBezierMovementLibrary::MoveObjectAlongCurve( UObject* WorldContextObject , AActor* Item , FVector StartPoint , FVector ControlPoint , FVector EndPoint , float Duration )
{
    if (!WorldContextObject || !Item)
        return;

    // 테스트용
    APickup* YourItem = Cast<APickup>( Item );
    if (YourItem)
    {
        YourItem->StartMovement( StartPoint , ControlPoint , EndPoint , Duration );
    }

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint , ControlPoint , EndPoint , Duration , 0.0f );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}

void UBezierMovementLibrary::UpdateObjectPosition( UObject* WorldContextObject , AActor* Item , FVector StartPoint , FVector ControlPoint , FVector EndPoint , float Duration , float Time )
{
    if (!WorldContextObject || !Item)
        return;

    if (Time >= Duration)
    {
        Item->SetActorLocation( EndPoint );
        return;
    }

    float t = Time / Duration;
    FVector NewPosition = FMath::Lerp(
        FMath::Lerp( StartPoint , ControlPoint , t ) ,
        FMath::Lerp( ControlPoint , EndPoint , t ) ,
        t
    );

    Item->SetActorLocation( NewPosition );

    FTimerDelegate TimerDelegate;
    TimerDelegate.BindStatic( &UBezierMovementLibrary::UpdateObjectPosition , WorldContextObject , Item , StartPoint , ControlPoint , EndPoint , Duration , Time + WorldContextObject->GetWorld()->GetDeltaSeconds() );

    WorldContextObject->GetWorld()->GetTimerManager().SetTimerForNextTick( TimerDelegate );
}