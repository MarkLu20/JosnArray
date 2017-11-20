// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonWriteRead.h"
#pragma region ��ȡjson



void UJsonWriteRead::WriteJson(FString _path, TArray<FJsonArray> jsonArry, bool &fail)
{
	FString jsonStr;
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> jsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&jsonStr);
	jsonWriter->WriteArrayStart();
	for (int i = 0; i < jsonArry.Num(); i++)
	{
		jsonWriter->WriteObjectStart();
		jsonWriter->WriteValue(TEXT("index"), jsonArry[i].JsonIndex);
		jsonWriter->WriteValue(TEXT("Jsoncont"), jsonArry[i].JsonCont);
		jsonWriter->WriteObjectEnd();
	}
	jsonWriter->WriteArrayEnd();
	jsonWriter->Close();
	FString path = FPaths::GameDir() / *_path;//����ϷĿ¼
    fail=FFileHelper::SaveStringToFile(jsonStr,*path);//�洢json�ļ�

}

#pragma endregion

TArray<FJsonArray> UJsonWriteRead::ReadJson(FString _path, bool & flag)
{           
	TArray<FJsonArray> JsonArry;
	FJsonArray JsonObjet;
	FString JsonValue;
	flag = FFileHelper::LoadFileToString(JsonValue,*_path);
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (FJsonSerializer::Deserialize(JsonReader,JsonParsed))
	{
		if (flag)
		{
			for (int i = 0; i < JsonParsed.Num(); i++)
			{
				JsonObjet.JsonIndex = JsonParsed[i]->AsObject()->GetStringField("index");
				JsonObjet.JsonCont = JsonParsed[i]->AsObject()->GetStringField("Jsoncont");

				JsonArry.Add(JsonObjet);
			}
		}
	}
	return JsonArry;
}

void UJsonWriteRead::CreateFolder(FString _path)
{
	//FPlatformFileManager::Get().GetPlatformFile().crea
}
////��ȡ��Ŀ��ǰĿ¼
//FString UFileDictOperationCollection::GetGameDir()
//{
//	const  FString _gamePath = FPaths::GameDir();
//
//	return _gamePath;
//}
//
////ɾ���ļ�
//void UFileDictOperationCollection::RemoveFile(FString _path)
//{
//	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*_path);
//	}
//}
//
////ɾ��Ŀ¼
//void UFileDictOperationCollection::RemoveFolder(FString _path)
//{
//	if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().DeleteDirectoryRecursively(*_path);
//	}
//}
//
////��ȡĳһĿ¼�µ������ļ�
//TArray<FString> UFileDictOperationCollection::GetFolderFiles(FString _path)
//{
//	TArray<FString> files;
//
//	FPaths::NormalizeDirectoryName(_path);
//	IFileManager& FileManager = IFileManager::Get();
//
//	FString FinalPath = _path / TEXT("*");
//	FileManager.FindFiles(files, *FinalPath, true, true);
//
//	return files;
//}
//
////�����ļ���
//void UFileDictOperationCollection::CreateFolder(FString _path)
//{
//	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*_path);
//	}
//}