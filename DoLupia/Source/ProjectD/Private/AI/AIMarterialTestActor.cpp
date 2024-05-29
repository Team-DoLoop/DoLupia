// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMarterialTestActor.h"
#include "IImageWrapperModule.h"
#include "Components/BoxComponent.h"
#include "Engine/Texture2D.h"
#include "UObject/Package.h"
#include "ImageUtils.h"
#include "Materials/MaterialInstance.h"
#include "Library/AIConnectionLibrary.h"
#include "Materials/MaterialExpressionTextureSample.h"
#include "Engine/Texture2DDynamic.h" 
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "Async/Async.h"
#include "TextureResource.h"
#include <Components/TimelineComponent.h>

// Sets default values
AAIMarterialTestActor::AAIMarterialTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    boxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "boxComp" ) );
    this->SetRootComponent( boxComp );

    meshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp" ) );
    meshComp->SetupAttachment( RootComponent );

    boxComp->SetCollisionEnabled( ECollisionEnabled::PhysicsOnly );
    meshComp->SetCollisionEnabled( ECollisionEnabled::PhysicsOnly );

    // Create Timeline component
    TimelineComponent = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComponent" ) );

    NewTexture = nullptr;
    InitialMaterial = nullptr;
    InitialTexture = nullptr;
    DynamicMaterial = nullptr;

    TimelineLength = 10.0f; // 설정하고자 하는 재생 시간

}

// Called when the game starts or when spawned
void AAIMarterialTestActor::BeginPlay()
{
	Super::BeginPlay();

    AIlib = NewObject<UAIConnectionLibrary>();

    // Bind UpdateAlpha function to the timeline
    FOnTimelineFloat TimelineProgress;
    TimelineProgress.BindUFunction( this , FName( "UpdateAlpha" ) );
    TimelineComponent->AddInterpFloat( AlphaCurve , TimelineProgress );
    TimelineComponent->SetTimelineLength( TimelineLength );
    TimelineComponent->SetTimelineLengthMode( ETimelineLengthMode::TL_LastKeyFrame );

    TimelineComponent->SetLooping( false );
    TimelineComponent->SetPlayRate( TimelineComponent->GetTimelineLength() / TimelineLength );
    //TimelineComponent->SetPlayRate( 0.5f ); // Example setting, change as needed

    // Bind OnTimelineFinished function to the timeline's finished event
    FOnTimelineEvent TimelineFinished;
    TimelineFinished.BindUFunction( this , FName( "OnTimelineFinished" ) );
    TimelineComponent->SetTimelineFinishedFunc( TimelineFinished );

    // Get the initial material
    
    InitialMaterial = meshComp->GetMaterial(0);
    if (InitialMaterial)
    {
        UE_LOG( LogTemp , Warning , TEXT( "BeginPlay::InitialMaterial" ) );
        DynamicMaterial = UMaterialInstanceDynamic::Create( InitialMaterial , this );
        if (DynamicMaterial)
        {
            meshComp->SetMaterial( 0 , DynamicMaterial );
        }
    }

    // Start the timeline
    TimelineComponent->PlayFromStart();

}

// Called every frame
void AAIMarterialTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIMarterialTestActor::UpdateActorMaterial()
{
    LoadWebImage();
}

void AAIMarterialTestActor::LoadWebImage()
{
    // Image Load URL Setting
    FString ServerURL = AIlib->SetupAITextureURL();

    // Image Downloading..
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( ServerURL );
    if (DownloadTask)
    {
        DownloadTask->OnSuccess.AddDynamic( this , &AAIMarterialTestActor::OnImageDownloaded );
        DownloadTask->OnFail.AddDynamic( this , &AAIMarterialTestActor::OnImageDownloadFailed );
    }

}

void AAIMarterialTestActor::OnImageDownloaded(UTexture2DDynamic* DownloadedTexture)
{
    if (DownloadedTexture)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded" ) );  
        // 다운로드된 텍스처를 머티리얼 인스턴스에 적용
        DynamicMaterial = meshComp->CreateDynamicMaterialInstance( 0 , MaterialTemplate );

        NewTexture = DownloadedTexture;

        if (DynamicMaterial && TimelineComponent && NewTexture)
        {
            UE_LOG( LogTemp , Warning , TEXT( "OnImageDownloaded - DynamicMaterial && TimelineComponent" ) );

            DynamicMaterial->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial->SetScalarParameterValue( FName( "Alpha" ) , 0.0f );
            TimelineComponent->SetNewTime( 20.0f );
            TimelineComponent->SetPlayRate( 0.25f );
            TimelineComponent->PlayFromStart();
            
           
            UE_LOG( LogTemp , Warning , TEXT( "TimelineComponent::PlayFromStart" ) );
        }

    }
}

void AAIMarterialTestActor::OnImageDownloadFailed(UTexture2DDynamic* DownloadedTexture)
{
    UE_LOG( LogTemp , Error , TEXT( "Failed to download image" ) );
}

void AAIMarterialTestActor::UpdateAlpha( float Alpha )
{   
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(FName("Alpha"), Alpha);
    }
    
}

void AAIMarterialTestActor::OnTimelineFinished()
{
    // Handle timeline finished event
    // For example, you can loop the timeline
    
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue( FName( "Alpha" ) , 1.0f );
    }
    
}
