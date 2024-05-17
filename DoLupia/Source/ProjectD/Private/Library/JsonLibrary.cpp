// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/JsonLibrary.h"

FString UJsonLibrary::JsonParse(const FString& data)
{
	FString result;

	// Json Reader 를 만든다.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(data);

	// Json Object 를 만든다.
	TSharedPtr<FJsonObject> obj = MakeShareable(new FJsonObject());

	// 해독(Deserialize)을 한다.
	if (FJsonSerializer::Deserialize(reader, obj))
	{
		/*
		auto response = obj->GetObjectField(TEXT("response"));
		auto body = response->GetObjectField(TEXT("body"));
		auto items = body->GetObjectField(TEXT("items"));

		TArray<TSharedPtr<FJsonValue>> item = items->GetArrayField("item");
		for (TSharedPtr<FJsonValue> pair : item)
		{
			FString title = pair->AsObject()->GetStringField("CON_TITLE");
			FString addr = pair->AsObject()->GetStringField("CON_ADDRESS");

			//FString title = TEXT("CON_TITLE");
			//FString addr = TEXT("CON_ADDRESS");
			UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *title, *addr)
			result.Append(FString::Printf(TEXT("title : %s / address : %s\n"), *title, *addr));
		}
		*/

		auto responses = obj->GetArrayField( TEXT( "response" ) );

		for (const auto& response : responses)
		{
			auto contentArray = response->AsObject()->GetArrayField( TEXT( "content" ) );
			for (const auto& content : contentArray)
			{
				UE_LOG( LogTemp, Warning, TEXT("string : [%s]"), *content->AsString() )
				if (content->Type == EJson::String)
				{
					FString contentString = content->AsString();
					result += FString::Printf( TEXT( "content : %s\n" ) , *contentString );
				}
				else
				{
					UE_LOG( LogJson , Warning , TEXT( "Field content is not a string" ) );
				}
			}
		}

	}


	return  result;
}

FString UJsonLibrary::MapToJsonInt(const TMap<FString, int32>& map)
{
	// JsonObj 를 생성
	TSharedPtr<FJsonObject> Jsonobj = MakeShareable(new FJsonObject());

	// map 의 내용을 JsonObj에 담음
	//for(TPair<FString, FString> pair : map)
	for (auto& pair : map)			//메모리를 새로 사용하지 않음 [&-> 원본을 사용하겠다.]
	{
		Jsonobj->SetNumberField(pair.Key, pair.Value);
	}

	// JsonObj를 encoding( = Serialize) 하고 싶다.
	FString jsonData;
	auto writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);

	FJsonSerializer::Serialize(Jsonobj.ToSharedRef(), writer);

	// 그것을 반환하고 싶다.
	return  jsonData;
}

FString UJsonLibrary::MapToJsonStr( const TMap<FString , FString>& map )
{
	// JsonObj 를 생성
	TSharedPtr<FJsonObject> Jsonobj = MakeShareable( new FJsonObject() );

	// map 의 내용을 JsonObj에 담음
	//for(TPair<FString, FString> pair : map)
	for (auto& pair : map)			//메모리를 새로 사용하지 않음 [&-> 원본을 사용하겠다.]
	{
		Jsonobj->SetStringField( pair.Key , pair.Value );
	}

	// JsonObj를 encoding( = Serialize) 하고 싶다.
	FString jsonData;
	auto writer = TJsonWriterFactory<TCHAR>::Create( &jsonData );

	FJsonSerializer::Serialize( Jsonobj.ToSharedRef() , writer );

	// 그것을 반환하고 싶다.
	return  jsonData;
}

bool UJsonLibrary::SaveJson(const FString& filename, const FString& json)
{
	//파일 매니저를 가져오고 싶다.
	FPlatformFileManager& fileManager = FPlatformFileManager::Get();
	IPlatformFile& platformfile = fileManager.GetPlatformFile();

	//만약 지정된 폴더가 없으면 해당 폴더를 만든다.
	FString directoryPath = FPaths::ProjectContentDir() + "jsonData";
	if (false == platformfile.DirectoryExists(*directoryPath))
	{
		platformfile.CreateDirectory(*directoryPath);
	}

	//json문자열을 파일로 저장한다.
	FString fullPath = directoryPath + "/" + filename;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), fullPath);

	bool bResult = FFileHelper::SaveStringToFile(json, *fullPath);
	if (false == bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Failed..."));
	}

	return bResult;

}
