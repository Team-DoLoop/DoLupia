// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AITxtBossAttack.h"
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
#include "Components/TimelineComponent.h"


// Sets default values
AAITxtBossAttack::AAITxtBossAttack()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "RootComponent" ) );

    meshComp1 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp1" ) );
    meshComp1->SetupAttachment( RootComponent );

    meshComp2 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp2" ) );
    meshComp2->SetupAttachment( RootComponent );

    meshComp3 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp3" ) );
    meshComp3->SetupAttachment( RootComponent );

    meshComp4 = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "meshComp4" ) );
    meshComp4->SetupAttachment( RootComponent );

    if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
    {
        UE_LOG( LogTemp , Error , TEXT( "Failed to create meshComps" ) );
    }

    TimelineComp = CreateDefaultSubobject<UTimelineComponent>( TEXT( "TimelineComponent" ) );
    TimelineLength = 5.0f; // 재생 시간

    NewTexture = nullptr;
    DynamicMaterial1 = nullptr;
    DynamicMaterial2 = nullptr;
    DynamicMaterial3 = nullptr;
    DynamicMaterial4 = nullptr;

}

// Called when the game starts or when spawned
void AAITxtBossAttack::BeginPlay()
{
    Super::BeginPlay();

    AIlib = NewObject<UAIConnectionLibrary>();

    // Timeline 진행 중
    FOnTimelineFloat TimelineProgress;
    TimelineProgress.BindUFunction( this , FName( "UpdateDissolve" ) );
    TimelineComp->AddInterpFloat( AlphaCurve , TimelineProgress );
    TimelineComp->SetTimelineLength( TimelineLength );
    TimelineComp->SetTimelineLengthMode( ETimelineLengthMode::TL_TimelineLength );

    TimelineComp->SetLooping( false );
    TimelineComp->SetPlayRate( TimelineComp->GetTimelineLength() / TimelineLength );
    //TimelineComponent->SetPlayRate( 0.5f ); // Example setting, change as needed

    // Timeline 끝날 때
    FOnTimelineEvent TimelineFinished;
    TimelineFinished.BindUFunction( this , FName( "OnTimelineFinished" ) );
    TimelineComp->SetTimelineFinishedFunc( TimelineFinished );

    if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
    {
        UE_LOG( LogTemp , Error , TEXT( "meshComps is nullptr in BeginPlay" ) );
        return;
    }


}

// Called every frame
void AAITxtBossAttack::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

}

void AAITxtBossAttack::UpdateActorMaterial()
{
    LoadWebImage();
}

void AAITxtBossAttack::UpdateDissolve( float dissolve )
{
    if (DynamicMaterial1)
    {
        DynamicMaterial1->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial2->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial3->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
        DynamicMaterial4->SetScalarParameterValue( FName( "dissolve" ) , dissolve );
    }
}

void AAITxtBossAttack::OnTimelineFinished()
{
    if (DynamicMaterial1)
    {
        DynamicMaterial1->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial2->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial3->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
        DynamicMaterial4->SetScalarParameterValue( FName( "dissolve" ) , 1.0f );
    }
}

void AAITxtBossAttack::LoadWebImage()
{
    // Image Load URL Setting
    FString ServerURL = AIlib->SetupAITextureURL();

    // Image Downloading..
    UAsyncTaskDownloadImage* DownloadTask = UAsyncTaskDownloadImage::DownloadImage( ServerURL );
    if (DownloadTask)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::LoadWebImage - Download" ) );
        DownloadTask->OnSuccess.AddDynamic( this , &AAITxtBossAttack::OnImageDownloaded );
        DownloadTask->OnFail.AddDynamic( this , &AAITxtBossAttack::OnImageDownloadFailed );
    }
}

void AAITxtBossAttack::OnImageDownloaded( UTexture2DDynamic* DownloadedTexture )
{
    if (DownloadedTexture)
    {
        UE_LOG( LogTemp , Warning , TEXT( "AAIMarterialTestActor::OnImageDownloaded" ) );
        // 다운로드된 텍스처를 머티리얼 인스턴스에 적용

        if (!meshComp1 || !meshComp2 || !meshComp3 || !meshComp4)
        {
            UE_LOG( LogTemp , Error , TEXT( "meshComp is nullptr - mesh" ) );
            return;
        }

        if (meshComp1 && meshComp2 && meshComp3 && meshComp4 && AITxtMaterial)
        {
            DynamicMaterial1 = meshComp1->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial2 = meshComp2->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial3 = meshComp3->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
            DynamicMaterial4 = meshComp4->CreateDynamicMaterialInstance( 0 , AITxtMaterial );
        }

        NewTexture = DownloadedTexture;
        if (DynamicMaterial1 && DynamicMaterial2 && DynamicMaterial3 && DynamicMaterial4)
        {
            DynamicMaterial1->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial2->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial3 ->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            DynamicMaterial4->SetTextureParameterValue( FName( "A1-2345" ) , NewTexture );
            
            TimelineComp->PlayFromStart();
        }
    }
}

void AAITxtBossAttack::OnImageDownloadFailed( UTexture2DDynamic* DownloadedTexture )
{
    UE_LOG( LogTemp , Error , TEXT( "Failed to download image" ) );
}

