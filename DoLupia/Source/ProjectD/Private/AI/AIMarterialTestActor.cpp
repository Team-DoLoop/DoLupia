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

    // Create dynamic material instance
    DynamicMaterial = meshComp->CreateDynamicMaterialInstance( 0 , MaterialTemplate );

    // Create Timeline component
    TimelineComponent = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComponent" ) );

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

    // Bind OnTimelineFinished function to the timeline's finished event
    FOnTimelineEvent TimelineFinished;
    TimelineFinished.BindUFunction( this , FName( "OnTimelineFinished" ) );
    TimelineComponent->SetTimelineFinishedFunc( TimelineFinished );

    // Play the timeline
    TimelineComponent->PlayFromStart();

    NewTexture = nullptr;

    // 초기 머티리얼을 가져옵니다.
    UMaterialInterface* InitialMaterial = meshComp->GetMaterial( 0 );
    if (InitialMaterial)
    {
        UMaterialInstanceDynamic* TempMaterial = UMaterialInstanceDynamic::Create( InitialMaterial , this );
        if (TempMaterial)
        {
            TempMaterial->GetTextureParameterValue( FName( "A1-2345" ) , InitialTexture );
            NewTexture = Cast<UTexture2DDynamic>( InitialTexture );
        }
    }
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
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Download" ) );
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
        TimelineComponent->PlayFromStart();

        // UTexture로 캐스팅
        UTexture* testTexture = Cast<UTexture>( DownloadedTexture );
        NewTexture = DownloadedTexture;

        

        if (DynamicMaterial && TimelineComponent)
        {
            //DynamicMaterial->SetScalarParameterValue( FName( "Alpha" ) , 0.0f );

            DynamicMaterial->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            TimelineComponent->PlayFromStart();
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
        DynamicMaterial->SetScalarParameterValue( FName( "Alpha" ) , Alpha );

        if (Alpha >= 1.0f && NewTexture)
        {
            // Set the new texture when Alpha is fully transitioned
            DynamicMaterial->SetTextureParameterValue( FName( "TextureParameter" ) , NewTexture );
            NewTexture = nullptr;

            // Reset alpha for next transition
            DynamicMaterial->SetScalarParameterValue( FName( "Alpha" ) , 0.0f );
        }
    }

    /*
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(FName("Alpha"), Alpha);
    }

    if (InitialTexture)
    {
        UMaterialInstanceDynamic* InitialDynamicMaterial = UMaterialInstanceDynamic::Create(MaterialTemplate, this);
        InitialDynamicMaterial->SetScalarParameterValue(FName("Alpha"), 1.0f - Alpha);
        InitialDynamicMaterial->SetTextureParameterValue(FName("A1-2345"), InitialTexture);
        MeshComp->SetMaterial(0, InitialDynamicMaterial);
    }
    */
}

void AAIMarterialTestActor::OnTimelineFinished()
{
    // Handle timeline finished event
    // For example, you can loop the timeline
    TimelineComponent->PlayFromStart();

    /*
    if (MeshComp && DynamicMaterial)
    {
        MeshComp->SetMaterial(0, DynamicMaterial);
        InitialTexture = nullptr;
    }
    */
}
