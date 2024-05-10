// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/Test/AITestWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Components/TextBlock.h"
#include "Library/JsonLibrary.h"
#include "ImageUtils.h"
#include "AI/AIMarterialTestActor.h"
#include "Components/Image.h"
#include "Engine.h"

void UAITestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_chatbot->OnClicked.AddDynamic(this, &UAITestWidget::SendChatbotSV);
	btn_imgAI->OnClicked.AddDynamic(this, &UAITestWidget::SendImgaiSV);
	btn_MLoad->OnClicked.AddDynamic( this , &UAITestWidget::ChangeMaterial );
}

void UAITestWidget::SendChatbotSV()
{
	TMap<FString, FString> msgData;
	FString msg = *edit_sendText->GetText().ToString();
	msgData.Add(TEXT("message"), msg);

	FString sendJson = UJsonLibrary::MapToJson(msgData);
	
	FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AIImgTxt.png";

	/* Server Conn URL */
	FString ServerURL = "http://" + LanIP + ":" + ServerPort + "/chat";

	// Server connect
	ReqDataPost( ServerURL , sendJson);
}

void UAITestWidget::SendImgaiSV()
{
	TMap<FString, FString> imgData;
	FString imgmsg = *edit_sendText->GetText().ToString();
	imgData.Add(TEXT("Img_keywords"), imgmsg);

	FString sendJson = UJsonLibrary::MapToJson(imgData);

	/* Server Conn URL */
	FString ServerURL = "http://" + LanIP + ":" + ServerPort + "/imageAI";

	// server connect
	ReqImgPost( ServerURL , sendJson);
}

void UAITestWidget::ChangeMaterial()
{
	UE_LOG( LogTemp , Warning , TEXT( "UAITestWidget::ChangeMaterial" ) );
	// Find the actor of type AYourActor
	for (TActorIterator<AAIMarterialTestActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UAITestWidget::ChangeMaterial - Searching Actors..." ) );
		// Call the function on the actor
		ActorItr->UpdateActorMaterial();
		
	}
}

void UAITestWidget::ReqDataPost(const FString& url, const FString& msg)
{
	// FHTTPModule 객체를 가져오고 싶다.
	auto& httpModule = FHttpModule::Get();

	// UHTTPRequest 객체를 만들고 싶다.
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// url 설정
	req->SetURL(url);

	// verb 설정 (post)
	req->SetVerb(TEXT("POST"));

	// header 설정
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// 보낼 정보를 담기
	req->SetContentAsString(msg);

	// 응답함수 등록
	req->OnProcessRequestComplete().BindUObject(this, &UAITestWidget::ResDataPost);

	// 요청 실행
	req->ProcessRequest();
	
}

void UAITestWidget::ResDataPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = Response->GetContentAsString();

		//result = UJsonLibrary::JsonParse(result);
		UE_LOG(LogTemp, Warning, TEXT("result : [%s]"), *result)
		txt_chatbot->SetText( FText::FromString( result ) );

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG(LogTemp, Warning, TEXT("Responce Failed... %d"), Response->GetResponseCode());
		}
	}
}

void UAITestWidget::ReqImgPost(const FString& url, const FString& msg)
{
	// FHTTPModule 객체를 가져오고 싶다.
	auto& httpModule = FHttpModule::Get();

	// UHTTPRequest 객체를 만들고 싶다.
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// url 설정
	req->SetURL( url );

	// verb 설정 (post)
	req->SetVerb( TEXT( "POST" ) );

	// header 설정
	req->SetHeader( TEXT( "Content-Type" ) , TEXT( "application/json" ) );

	// 보낼 정보를 담기
	req->SetContentAsString( msg );

	// 응답함수 등록
	req->OnProcessRequestComplete().BindUObject( this , &UAITestWidget::ResAIImage );

	// 요청 실행
	req->ProcessRequest();
}

void UAITestWidget::ResAIImage( FHttpRequestPtr Request , FHttpResponsePtr Response , bool bConnectedSuccessfully )
{
	if (bConnectedSuccessfully)
	{
		//바이트 배열에 응답받은 콘텐츠를 가져오고 싶다.
		TArray<uint8> buf = Response->GetContent();

		//저장한 이미지의 경로를 정하고 싶다
		FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AIImgTxt.png";
		UE_LOG( LogTemp , Warning , TEXT( "result : [%s]" ) , *imgPath )

		//FFileHelper의 save 함수를 통해 파일로 저장한다.
		FFileHelper::SaveArrayToFile( buf , *imgPath );

		//바이트 배열을 이미지로 변환한다.
		UTexture2D* txt = FImageUtils::ImportBufferAsTexture2D( buf );

		//그 이미지를 ui에 적용한다.
		img_aitexture->SetBrushFromTexture( txt );

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Response Failed... %d" ) , Response->GetResponseCode() );
		}
	}
}
