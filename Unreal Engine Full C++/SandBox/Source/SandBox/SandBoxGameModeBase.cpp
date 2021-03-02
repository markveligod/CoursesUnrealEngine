// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandBoxGameModeBase.h"
#include "Public/Pawns/SandBoxPawn.h"
#include "Public/PlayerControllers/SandBoxPlayerController.h"


ASandBoxGameModeBase::ASandBoxGameModeBase()
{
	DefaultPawnClass = ASandBoxPawn::StaticClass();
	PlayerControllerClass = ASandBoxPlayerController::StaticClass();
}
