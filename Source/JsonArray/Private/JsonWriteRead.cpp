// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonWriteRead.h"
#pragma region 读取json



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
	FString path = FPaths::GameDir() / *_path;//打开游戏目录
    fail=FFileHelper::SaveStringToFile(jsonStr,*path);//存储json文件

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
////获取项目当前目录
//FString UFileDictOperationCollection::GetGameDir()
//{
//	const  FString _gamePath = FPaths::GameDir();
//
//	return _gamePath;
//}
//
////删除文件
//void UFileDictOperationCollection::RemoveFile(FString _path)
//{
//	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*_path);
//	}
//}
//
////删除目录
//void UFileDictOperationCollection::RemoveFolder(FString _path)
//{
//	if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().DeleteDirectoryRecursively(*_path);
//	}
//}
//
////获取某一目录下的所有文件
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
////创建文件夹
//void UFileDictOperationCollection::CreateFolder(FString _path)
//{
//	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*_path))
//	{
//		FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*_path);
//	}
//}