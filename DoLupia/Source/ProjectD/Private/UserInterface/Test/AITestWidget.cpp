// Fill out your copyright notice in the Description page of Project Settings.

#include "UserInterface/Test/AITestWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Library/JsonLibrary.h"

void UAITestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_chatbot->OnClicked.AddDynamic(this, &UAITestWidget::SendChatbotSV);
	btn_imgAI->OnClicked.AddDynamic(this, &UAITestWidget::SendImgaiSV);
}

void UAITestWidget::SendChatbotSV()
{
	TMap<FString, FString> msgData;
	FString msg = *edit_sendText->GetText().ToString();
	msgData.Add(TEXT("message"), msg);

	FString sendJson = UJsonLibrary::MapToJson(msgData);
	FString fullURL = "http://127.0.0.1:8000/chat";

	// server connect
	ReqDataPost(fullURL, sendJson);
}

void UAITestWidget::SendImgaiSV()
{
	TMap<FString, FString> imgData;
	FString imgmsg = *edit_sendText->GetText().ToString();
	imgData.Add(TEXT("message"), imgmsg);

	FString sendJson = UJsonLibrary::MapToJson(imgData);

	FString fullURL = "http://127.0.0.1:8000/imgai";
	//ReqDataPost(fullURL, sendJson);
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
		UE_LOG(LogTemp, Warning, TEXT("result : [%s]"), *result)

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG(LogTemp, Warning, TEXT("Responce Failed... %d"), Response->GetResponseCode());
		}
	}
}
