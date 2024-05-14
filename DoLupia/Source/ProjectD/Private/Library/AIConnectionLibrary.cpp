// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/AIConnectionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "ImageUtils.h"
#include "Library/JsonLibrary.h"


void UAIConnectionLibrary::SendNPCConversationToServer( const FString& message )
{
	TMap<FString , FString> msgData;
	FString msg = message;
	msgData.Add( TEXT( "message" ) , msg );

	FString sendJson = UJsonLibrary::MapToJson( msgData );

	/* AI Server Connection */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/chat";
	ReqMessage( ServerURL , sendJson );
}

void UAIConnectionLibrary::SendImageKeywordToServer(const FString& keyword )
{
	TMap<FString , FString> imgData;
	FString ImgKeyword = keyword;
	imgData.Add( TEXT( "Img_keywords" ) , ImgKeyword );

	FString sendJson = UJsonLibrary::MapToJson( imgData );

	/* AI Server Connection */
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/imageAI";
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
	if (bConnectedSuccessfully)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Response Success... %d" ) , Response->GetResponseCode() );
		
		FString result = Response->GetContentAsString();
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *result )

		//나중에 여기서 받은 문자열을 NPC 혹은 gamemode 에 보내는 로직 필요
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}

}


void UAIConnectionLibrary::ReqAIImage(const FString& url, const FString& msg)
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

		TArray<uint8> buf = Response->GetContent();

		// Image path
		FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AITexture.png";
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *imgPath )

		// Save Image to File
		FFileHelper::SaveArrayToFile( buf , *imgPath );

		// 추후, image -> texture file 로 변환하는 로직 필요 (따로 함수로 기능 구현)
	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}
}
