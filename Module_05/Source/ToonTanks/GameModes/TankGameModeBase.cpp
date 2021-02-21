// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ATankGameModeBase::BeginPlay() 
{
    // Get references and game win/lose conditions. 

    // Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc. 

    this->HandleGameStart();
}

void ATankGameModeBase::HandleGameStart() 
{
    // Initialise the start countdown, turret activation, pawn check etc. 
    // Call Blueprint version GameStart();
    this->TargetTurrets = this->CalcCountTurrets();
    this->PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    this->GameStart();

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
     // See if the player has destroyed all the turrets, show win result.
    // else if turret destroyed player, show lose result. 
    // Call blueprint version GameOver(bool).
    this->GameOver(PlayerWon);
}

int32 ATankGameModeBase::CalcCountTurrets() 
{
    TArray<AActor *> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return(TurretActors.Num());
}

void ATankGameModeBase::ActorDied(AActor * DeadActor) 
{
    if (DeadActor == this->PlayerTank)
    {
        this->PlayerTank->HandleDestruction();
        this->HandleGameOver(false);
    }
    else if (APawnTurret * Destroyed = Cast<APawnTurret>(DeadActor))
    {
        Destroyed->HandleDestruction();
        this->TargetTurrets = this->CalcCountTurrets();
        if (this->TargetTurrets == 0)
            this->HandleGameOver(true);
    }
}
