// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/JsonLibrary.h"

FString UJsonLibrary::JsonParse(const FString& data)
{
	FString result;

	// Json Reader �� �����.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(data);

	// Json Object �� �����.
	TSharedPtr<FJsonObject> obj = MakeShareable(new FJsonObject());

	// �ص�(Deserialize)�� �Ѵ�.
	if (FJsonSerializer::Deserialize(reader, obj))
	{
		UE_LOG(LogTemp, Warning, TEXT("TEST1"))
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

	}


	return  result;
}

FString UJsonLibrary::MapToJson(const TMap<FString, FString>& map)
{
	// JsonObj �� ����
	TSharedPtr<FJsonObject> Jsonobj = MakeShareable(new FJsonObject());

	// map �� ������ JsonObj�� ����
	//for(TPair<FString, FString> pair : map)
	for (auto& pair : map)			//�޸𸮸� ���� ������� ���� [&-> ������ ����ϰڴ�.]
	{
		Jsonobj->SetStringField(pair.Key, pair.Value);
	}

	// JsonObj�� encoding( = Serialize) �ϰ� �ʹ�.
	FString jsonData;
	auto writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);

	FJsonSerializer::Serialize(Jsonobj.ToSharedRef(), writer);

	// �װ��� ��ȯ�ϰ� �ʹ�.
	return  jsonData;
}

bool UJsonLibrary::SaveJson(const FString& filename, const FString& json)
{
	//���� �Ŵ����� �������� �ʹ�.
	FPlatformFileManager& fileManager = FPlatformFileManager::Get();
	IPlatformFile& platformfile = fileManager.GetPlatformFile();

	//���� ������ ������ ������ �ش� ������ �����.
	FString directoryPath = FPaths::ProjectContentDir() + "jsonData";
	if (false == platformfile.DirectoryExists(*directoryPath))
	{
		platformfile.CreateDirectory(*directoryPath);
	}

	//json���ڿ��� ���Ϸ� �����Ѵ�.
	FString fullPath = directoryPath + "/" + filename;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), fullPath);

	bool bResult = FFileHelper::SaveStringToFile(json, *fullPath);
	if (false == bResult)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Failed..."));
	}

	return bResult;

}
