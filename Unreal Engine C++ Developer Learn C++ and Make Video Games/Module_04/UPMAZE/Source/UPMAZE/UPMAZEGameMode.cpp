// Copyright Epic Games, Inc. All Rights Reserved.

#include "UPMAZEGameMode.h"
#include "UPMAZECharacter.h"
#include "UObject/ConstructorHelpers.h"

AUPMAZEGameMode::AUPMAZEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
