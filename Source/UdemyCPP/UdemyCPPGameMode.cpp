// Copyright Epic Games, Inc. All Rights Reserved.

#include "UdemyCPPGameMode.h"
#include "UdemyCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUdemyCPPGameMode::AUdemyCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
