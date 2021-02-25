// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/Controller.h"

void APlayerControllerBase::SetPlayerEnableState(bool SetPlayerEnabled) 
{
    if (SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = SetPlayerEnabled;
}
