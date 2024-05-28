// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/AIConnectionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"
#include "Engine.h"
#include "AI/AIMarterialTestActor.h"
#include "UserInterface/NPC/NPCConvWidget.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/JsonLibrary.h"
#include "NPC/NPCBase.h"

FString UAIConnectionLibrary::LanIP = "192.168.75.108";
//FString UAIConnectionLibrary::WifiIP = "172.16.216.55";
FString UAIConnectionLibrary::WifiIP = "172.16.216.55";
FString UAIConnectionLibrary::ServerPort = "8000";

UAIConnectionLibrary* UAIConnectionLibrary::Instance = nullptr;

UAIConnectionLibrary* UAIConnectionLibrary::GetInstance( UObject* WorldContextObject )
{
	if (!Instance)
	{
		Instance = NewObject<UAIConnectionLibrary>();
		Instance->AddToRoot();  // Prevents garbage collection
		Instance->Initialize( WorldContextObject );
	}

	return Instance;
}

void UAIConnectionLibrary::SendNPCConversationToServer( const FString& message )
{

	TMap<FString , FString> msgData;
	FString msg = message;
	msgData.Add( TEXT( "message" ) , msg );

	FString sendJson = UJsonLibrary::MapToJsonStr( msgData );

	/* AI Server Connection */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/chat";
	ReqMessage( ServerURL , sendJson );
}

void UAIConnectionLibrary::SendImageKeywordToServer( int32 keyword )
{
	//TMap<FString , FString> imgData;
	//FString ImgKeyword = keyword;

	TMap<FString , int32> imgData;
	int32 ImgKeyword = keyword;

	imgData.Add( TEXT( "Img_keywords" ) , ImgKeyword );

	FString sendJson = UJsonLibrary::MapToJsonInt( imgData );

	/* AI Server Image Request */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/imageAI";
	ReqAIImage( ServerURL , sendJson );


}

void UAIConnectionLibrary::LoadImageToMaterial()
{
	for (TActorIterator<AAIMarterialTestActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UAITestWidget::ChangeMaterial - Searching Actors..." ) );
		// Call the function on the actor
		ActorItr->LoadWebImage();

	}
}

FString UAIConnectionLibrary::SetupAITextureURL()
{
	/* AI Server Connection */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/ShowAITexture";

	return ServerURL;
}

void UAIConnectionLibrary::SendPImgToSrv( int32 keyword )
{
	TMap<FString , int32> playerData;
	int32 PImgKeyword = keyword;

	playerData.Add( TEXT( "Img_keywords" ) , PImgKeyword );

	FString sendJson = UJsonLibrary::MapToJsonInt( playerData );

	/* AI Server Image Request */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/CreatePlayerCapeTxt";
	ReqAIImage( ServerURL , sendJson );
}

void UAIConnectionLibrary::SendBImgToSrv( int32 keyword )
{
	TMap<FString , int32> bossimgData;
	int32 BImgKeyword = keyword;

	bossimgData.Add( TEXT( "Img_keywords" ) , BImgKeyword );

	FString sendJson = UJsonLibrary::MapToJsonInt( bossimgData );

	/* AI Server Image Request */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/CreateBossEffectsTxt";
	ReqAIImage( ServerURL , sendJson );
}

void UAIConnectionLibrary::ReqMessage(const FString& url, const FString& msg)
{
	auto& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL( url );
	req->SetVerb( TEXT( "POST" ) );
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );
	req->SetContentAsString( msg );

	req->OnProcessRequestComplete().BindUObject( this, &UAIConnectionLibrary::ResMessage );
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResMessage(FHttpRequestPtr Request, FHttpResponsePtr Response,
	bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully && Response.IsValid())
	{
		UE_LOG( LogTemp , Warning , TEXT( "Response Success... %d" ) , Response->GetResponseCode() );
		
		FString result = Response->GetContentAsString();
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *result )
		OnWebApiResponseReceived.Broadcast( result );

		UE_LOG( LogTemp , Warning , TEXT( "result - delegate test : [%s]" ) , *result )
	

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}

}


void UAIConnectionLibrary::ReqAIImage(const FString& url, const FString& msg )
{
	auto& httpModule = FHttpModule::Get();
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL( url );
	req->SetVerb( TEXT( "POST" ) );
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );
	req->SetContentAsString( msg );
	req->OnProcessRequestComplete().BindUObject( this , &UAIConnectionLibrary::ResAIImage );
	req->ProcessRequest();
}

void UAIConnectionLibrary::ResAIImage(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Response Success... %d" ) , Response->GetResponseCode() );

		// 이미지 저장 로직 저장 X -> 서버에서 생성된 이미지를 띄우는 형식으로 변경
		/*
		TArray<uint8> buf = Response->GetContent();
		FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AITexture.png";
		FFileHelper::SaveArrayToFile( buf , *imgPath );
		*/
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}
}

void UAIConnectionLibrary::Initialize( UObject* WorldContextObject )
{
	if (!WorldContextObject)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UAIConnectionLibrary::Initialize - Invalid WorldContextObject" ) );
		return;
	}

	// Store the WorldContextObject
	WorldContext = WorldContextObject;

	// Ensure the Http module is loaded and ready
	if (!FModuleManager::Get().IsModuleLoaded( "Http" ))
	{
		FModuleManager::Get().LoadModule( "Http" );
	}

	// You can add additional initialization code here as needed
	UE_LOG( LogTemp , Log , TEXT( "UAIConnectionLibrary initialized with WorldContextObject: %s" ) , *WorldContextObject->GetName() );
}
