// Fill out your copyright notice in the Description page of Project Settings.

#pragma once // it prevents to include the same file twice 

#include "CoreMinimal.h" 
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 *
 */
UCLASS(Blueprintable) // this will allow us to create a blueprint derived from that C++ class
class UDEMYCPP_API UMyObject : public UObject
{
	GENERATED_BODY()

};