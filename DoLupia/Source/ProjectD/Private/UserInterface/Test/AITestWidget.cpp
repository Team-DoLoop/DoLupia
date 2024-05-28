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
#include "AI/AITxtPlayer.h"
#include "Components/Image.h"
#include "Engine.h"
#include "Gamemode/PlayerGameMode.h"
#include "Library/AIConnectionLibrary.h"

void UAITestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	connectionLibrary = NewObject<UAIConnectionLibrary>();
	gm = Cast<APlayerGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );

	btn_chatbot->OnClicked.AddDynamic(this, &UAITestWidget::SendChatbotSV);
	btn_imgAI->OnClicked.AddDynamic(this, &UAITestWidget::SendImgaiSV);
	btn_MLoad->OnClicked.AddDynamic( this , &UAITestWidget::ChangeMaterial );
}

void UAITestWidget::SendChatbotSV()
{
	//UAIConnectionLibrary* connectionLibrary = NewObject<UAIConnectionLibrary>();

	TMap<FString, FString> msgData;
	FString msg = *edit_sendText->GetText().ToString();

	connectionLibrary->SendNPCConversationToServer( msg );

	//UE_LOG( LogTemp , Warning , TEXT( "test : [%s]" ) , *test )
	//txt_chatbot->SetText( FText::FromString( test) );

	//msgData.Add(TEXT("message"), msg);

	/*
	FString sendJson = UJsonLibrary::MapToJson(msgData);
	
	//FString imgPath = FPaths::ProjectContentDir() + "/AI/Texture/AIImgTxt.png";

	Server Conn URL 
	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/chat";

	// Server connect
	ReqDataPost( ServerURL , sendJson);
	*/
}

void UAITestWidget::SendImgaiSV()
{
	TMap<FString, FString> imgData;
	FString imgmsg = *edit_sendText->GetText().ToString();

	int32 tmpNum = 1;

	connectionLibrary->SendImageKeywordToServer( tmpNum );

	/*
	imgData.Add(TEXT("Img_keywords"), imgmsg);

	FString sendJson = UJsonLibrary::MapToJson(imgData);

	FString ServerURL = "http://" + WifiIP + ":" + ServerPort + "/imageAI";
	ReqImgPost( ServerURL , sendJson);
	*/
}

void UAITestWidget::ChangeMaterial()
{
	// Find the actor of type AYourActor
	for (TActorIterator<AAIMarterialTestActor> ActorItr( GetWorld() ); ActorItr; ++ActorItr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "UAITestWidget::ChangeMaterial - Searching Actors..." ) );
		// Call the function on the actor
		ActorItr->UpdateActorMaterial();
		
	}
	

	//gm->ApplyAITxtP();
}