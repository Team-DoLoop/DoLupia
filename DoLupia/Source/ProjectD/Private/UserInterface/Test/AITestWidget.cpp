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
	ReqDataPost(fullURL, sendJson);
}

void UAITestWidget::ReqDataPost(const FString& url, const FString& msg)
{
	// FHTTPModule ��ü�� �������� �ʹ�.
	auto& httpModule = FHttpModule::Get();

	// UHTTPRequest ��ü�� ����� �ʹ�.
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();

	// url ����
	req->SetURL(url);

	// verb ���� (post)
	req->SetVerb(TEXT("POST"));

	// header ����
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	// ���� ������ ���
	req->SetContentAsString(msg);

	// �����Լ� ���
	req->OnProcessRequestComplete().BindUObject(this, &UAITestWidget::ResDataPost);

	// ��û ����
	req->ProcessRequest();
	
}

void UAITestWidget::ResDataPost(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString result = Response->GetContentAsString();
		//UE_LOG(LogTemp, Warning, TEXT("result : [%s]"), result)

	}
	else
	{
		if (Request->GetStatus() == EHttpRequestStatus::Succeeded)
		{
			UE_LOG(LogTemp, Warning, TEXT("Responce Failed... %d"), Response->GetResponseCode());
		}
	}
}
