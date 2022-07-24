// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/ObjectMacros.h"
/**
 * 
 */

UENUM(BlueprintType)
enum ECustomMovementMode
{
	CMOVE_Climbing      UMETA(DisplayName = "Climbing"),
	CMOVE_MAX			UMETA(Hidden),
};

// Integrate the MovementMode to MainCharacter other Enums
