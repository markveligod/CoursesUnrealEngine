// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	this->TargetStartYaw = GetOwner()->GetActorRotation().Yaw;
	this->TargetEndYaw = GetOwner()->GetActorRotation().Yaw + this->RollValue;
	this->OpenDoor = FRotator(GetOwner()->GetActorRotation().Roll, GetOwner()->GetActorRotation().Yaw, GetOwner()->GetActorRotation().Pitch);

	if (!this->PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("%s NULL pointer"), *GetOwner()->GetName());

	this->ActorPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (this->SpeedOpenCloseDoor > 1.0f && this->SpeedOpenCloseDoor < 0)
		this->SpeedOpenCloseDoor = 1.0f;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (this->PressurePlate && this->PressurePlate->IsOverlappingActor(this->ActorPawn))
	{
		this->OpenDoorRun(DeltaTime);
		this->DoorLastOpen = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() > this->DoorLastOpen + this->DoorCloseDelay)
			this->CloseDoorRun(DeltaTime);
	}
}

void UOpenDoor::OpenDoorRun(float DeltaTime)
{
	float TempYaw = GetOwner()->GetActorRotation().Yaw;
	if (TempYaw < this->TargetEndYaw)
	{
		this->OpenDoor.Yaw = FMath::Lerp(TempYaw, this->TargetEndYaw, DeltaTime * this->SpeedOpenCloseDoor);
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), this->OpenDoor.Yaw);
		GetOwner()->SetActorRotation(this->OpenDoor);
	}
}

void UOpenDoor::CloseDoorRun(float DeltaTime)
{
	float TempYaw = GetOwner()->GetActorRotation().Yaw;
	if (TempYaw > this->TargetStartYaw + 2.f)
	{
		this->OpenDoor.Yaw = FMath::Lerp(TempYaw, this->TargetStartYaw, DeltaTime * this->SpeedOpenCloseDoor);
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), this->OpenDoor.Yaw);
		GetOwner()->SetActorRotation(this->OpenDoor);
	}
}
