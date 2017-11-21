// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Json.h"
#include "Paths.h"
#include "JsonWriteRead.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FJsonArray
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString JsonIndex;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString JsonCont;

};
UCLASS()
class JSONARRAY_API UJsonWriteRead : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Json")
		static void WriteJson(FString _path, TArray<FJsonArray> jsonArry,bool &fail);
	UFUNCTION(BlueprintCallable, Category = "Json")
		static void ReadJson(FString _path,bool &flag, TArray<FJsonArray> &JsonArry);
	UFUNCTION(BlueprintCallable, Category = "Folder")
		static void CreateFolder(FString _path);
	UFUNCTION(BlueprintCallable, Category = "Folder")
		static void DeleteFolder(FString _path);


};
