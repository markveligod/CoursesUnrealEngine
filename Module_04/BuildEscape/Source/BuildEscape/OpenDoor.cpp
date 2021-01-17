// Fill out your copyright notice in the Description page of Project Settings.


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
	this->TargetEndYaw = GetOwner()->GetActorRotation().Yaw + this->RollValue;
	this->OpenDoor = FRotator(GetOwner()->GetActorRotation().Roll, GetOwner()->GetActorRotation().Yaw, GetOwner()->GetActorRotation().Pitch);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (this->PressurePlate->IsOverlappingActor(this->ActorPawn))
		this->OpenDoorRun(DeltaTime);
}

void UOpenDoor::OpenDoorRun(float DeltaTime)
{
	float TempYaw = GetOwner()->GetActorRotation().Yaw;
	if (TempYaw < this->TargetEndYaw)
	{
		this->OpenDoor.Yaw = FMath::FInterpConstantTo(TempYaw, this->TargetEndYaw, DeltaTime, 50);
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), this->OpenDoor.Yaw);
		GetOwner()->SetActorRotation(this->OpenDoor);
	}
}