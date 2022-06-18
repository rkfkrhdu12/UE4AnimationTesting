// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnimTestProjectGameMode.h"
#include "AnimTestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAnimTestProjectGameMode::AAnimTestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
