// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APawnBase::APawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = this->CapsuleComp;

	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	this->BaseMesh->SetupAttachment(RootComponent);

	this->TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	this->TurretMesh->SetupAttachment(this->BaseMesh);

	this->ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	this->ProjectileSpawnPoint->SetupAttachment(this->TurretMesh);
	UE_LOG(LogTemp, Warning, TEXT("Create Constructor Pawn"));
}

void APawnBase::RotateTurrentFunction(FVector LookAtTarget) 
{
	//update TurrentMesh rotation to face towards the LookAtTarget
	// TurrentMesh->SetWorldRotation();
	FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, this->TurretMesh->GetComponentLocation().Z);
	
	FVector StartLocation = this->TurretMesh->GetComponentLocation();

	FRotator Temp = FVector(LookAtTargetClean - StartLocation).Rotation();
	this->TurretMesh->SetWorldRotation(Temp);

}

void APawnBase::Fire() 
{
	//Get ProjectileSpawnPoint Location && Rotation - > Spawn Projectile class at Location firing towards Rotation
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
}

void APawnBase::HandleDestruction() 
{
	// --- Universal functionality --- 
	// Play death effects particle, sound and camera shake. 

	// --- Then do Child overrides ---
	// -- PawnTurret - Inform GameMode Turret died -> Then Destroy() self. 

	// -- PawnTank - Inform GameMode Player died -> Then Hide() all components && stop movement input.

}
