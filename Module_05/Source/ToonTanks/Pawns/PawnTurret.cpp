// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(this->FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, this->FireRate, true);

    this->PlayerPawnTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (this->PlayerPawnTank && this->ReturnDistanceToPlayer() <= this->FireRange)
    {
        Super::RotateTurrentFunction(this->PlayerPawnTank->GetActorLocation());
    }
}

void APawnTurret::CheckFireCondition() 
{
    // if Player == null || is Dead
    if (!this->PlayerPawnTank)
    {
        return ;
    }

    //if Player is in range Then Fire
    if (this->ReturnDistanceToPlayer() <= this->FireRange && this->PlayerPawnTank->GetIsPlayerAlive())
    {
        Super::Fire();
    }
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if (!this->PlayerPawnTank)
    {
        return (0.f);
    }

    float Distance = FVector::Dist(this->PlayerPawnTank->GetActorLocation(), this->GetActorLocation());
    return (Distance);
}
