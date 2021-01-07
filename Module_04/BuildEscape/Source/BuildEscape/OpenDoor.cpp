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
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float TempYaw;
	if ((TempYaw = GetOwner()->GetActorRotation().Yaw) < 88.f)
	{
		FRotator OpenDoor(0.f, this->TargetYaw, 0.f);
		OpenDoor.Yaw = FMath::FInterpConstantTo(TempYaw, this->TargetYaw, DeltaTime, 50);
		UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), OpenDoor.Yaw);
		GetOwner()->SetActorRotation(OpenDoor);
	}
}

