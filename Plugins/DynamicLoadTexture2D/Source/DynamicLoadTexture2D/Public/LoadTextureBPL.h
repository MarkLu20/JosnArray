// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/ImageWrapper/Public/ImageWrapper.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h" 
#include  "PlatformFilemanager.h"
#include "Paths.h"
#include "FileHelper.h"
#include"Runtime/Engine//Classes/Engine/Texture2D.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapperModule.h"
#include "LoadTextureBPL.generated.h"

/**
 *
 */
UCLASS()
class DYNAMICLOADTEXTURE2D_API ULoadTextureBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		 
public:
	//FString diectory="";
	
	UFUNCTION(BlueprintCallable, Category = "LoadTexture")
		static UTexture2D* LoadTexture2D(FString ImagePath, bool& IsValid, int32& OutWidth, int32& OutHeight);
	UFUNCTION(BlueprintCallable, Category = "LoadTexture")
		static void EnsureDiectory(FString path);
	




};
static IImageWrapperPtr GetImageWrapperByExtention(FString InImagePath);
static FString cachePath;
