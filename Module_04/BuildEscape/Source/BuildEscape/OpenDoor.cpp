// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "OpenDoor.h"


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
	if (this->CheckStartFunc())
	{
		this->FindAudioComponent();
		this->TargetStartYaw = GetOwner()->GetActorRotation().Yaw;
		this->TargetEndYaw = GetOwner()->GetActorRotation().Yaw + this->RollValue;
		this->OpenDoor = FRotator(GetOwner()->GetActorRotation().Roll, GetOwner()->GetActorRotation().Yaw, GetOwner()->GetActorRotation().Pitch);
		this->ActorPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (this->SpeedOpenCloseDoor > 1.0f && this->SpeedOpenCloseDoor < 0)
			this->SpeedOpenCloseDoor = 1.0f;
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->CheckStartFunc())
	{	
		if (this->PressurePlate && this->PressurePlate->IsOverlappingActor(this->Key))
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
}

void UOpenDoor::OpenDoorRun(float DeltaTime)
{
	float TempYaw = GetOwner()->GetActorRotation().Yaw;
	if (TempYaw < this->TargetEndYaw)
	{
		this->OpenDoor.Yaw = FMath::Lerp(TempYaw, this->TargetEndYaw, DeltaTime * this->SpeedOpenCloseDoor);
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), this->OpenDoor.Yaw);
		GetOwner()->SetActorRotation(this->OpenDoor);

		if (this->OpenDoorSound)
		{
			this->AudioComp->Play();
			this->OpenDoorSound = false;
			this->CloseDoorSound = true;
		}
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

		if (this->CloseDoorSound)
		{
			this->AudioComp->Play();
			this->CloseDoorSound = false;
			this->OpenDoorSound = true;
		}
	}
}

float UOpenDoor::TotalMassOfActor() const
{
	float TotalMass = 0.f;

	//Find Actor
	TArray<AActor*> OverLappingActors;
	this->PressurePlate->GetOverlappingActors(OverLappingActors);
	for (AActor * Actor : OverLappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return (TotalMass);
}

bool UOpenDoor::CheckStartFunc() const
{
	if (!this->Key)
	{
		UE_LOG(LogTemp, Error, TEXT("НЕ УКАЗАН КЛЮЧ ИДИОТ у %s"), *GetOwner()->GetName());
		return (false);
	}
	if (!this->PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("НЕ УКАЗАН ТРИГГЕР ИДИОТ у %s"), *GetOwner()->GetName());
		return (false);
	}
	return (true);
}

void UOpenDoor::FindAudioComponent()
{
	this->AudioComp = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!this->AudioComp)
		UE_LOG(LogTemp, Error, TEXT("Audio Component dont found!"));
}
