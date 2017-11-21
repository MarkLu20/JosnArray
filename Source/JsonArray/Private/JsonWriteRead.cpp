// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonWriteRead.h"
#pragma region //写入json数据储存到本地文件中



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
	_path = FPaths::GameDir() / *_path;//打开游戏目录
	fail = FFileHelper::SaveStringToFile(jsonStr, *_path);//存储json文件

}

#pragma endregion
void UJsonWriteRead::ReadJson(FString _path, bool & flag, TArray<FJsonArray> &JsonArry)
{
	FJsonArray JsonObjet;
	FString JsonValue;
	_path = FPaths::GameDir() / *_path;//打开游戏目录
	flag = FFileHelper::LoadFileToString(JsonValue, *_path);
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
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

}
//在游戏目录下创建文件
void UJsonWriteRead::CreateFolder(FString _path)
{
	_path = FPaths::GameDir() / *_path;
	_path = FPaths::ConvertRelativePathToFull(*_path);

	FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*_path);

}
//删除该文件以及子文件
void UJsonWriteRead::DeleteFolder(FString _path)
{
	_path = FPaths::GameDir() / *_path;
	_path = FPaths::ConvertRelativePathToFull(*_path);
	FPlatformFileManager::Get().Get().GetPlatformFile().DeleteDirectoryRecursively(*_path);
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