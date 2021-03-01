// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandBoxGameModeBase.h"
#include "Public/Pawns/SandBoxPawn.h"


ASandBoxGameModeBase::ASandBoxGameModeBase()
{
	DefaultPawnClass = ASandBoxPawn::StaticClass();
}
