// Fill out your copyright notice in the Description page of Project Settings.


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

	if (this->TriggerKey && this->Key && this->Character)
	{
		this->StartLocalTheDoor = GetOwner()->GetActorRotation().Yaw;
		this->EndLocalTheDoor = this->StartLocalTheDoor + this->DistTheDoor;
		this->TempLocalTheDoor = this->StartLocalTheDoor;

		this->PhysicsHandle = this->Character->FindComponentByClass<UPhysicsHandleComponent>();
		if (this->PhysicsHandle)
			this->bOpenStart = true;
	}
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->bOpenStart)
	{
		if (this->TriggerKey->IsOverlappingActor(this->Key))
		{
			if (this->PhysicsHandle->GrabbedComponent)
				this->SetupKey();
			this->StartOpenTheDoor(DeltaTime);
		}
	}

}

void UOpenDoor::StartOpenTheDoor(float delta)
{
	FRotator TempVectorLocalTheDoor = GetOwner()->GetActorRotation();
	this->TempLocalTheDoor = FMath::Lerp(this->TempLocalTheDoor, this->EndLocalTheDoor, delta * this->PowerTheDoor);
	TempVectorLocalTheDoor.Yaw = this->TempLocalTheDoor;
	GetOwner()->SetActorRotation(TempVectorLocalTheDoor);
}

void UOpenDoor::SetupKey()
{
	this->PhysicsHandle->ReleaseComponent();
	FVector LocationTrigger = this->TriggerKey->GetActorLocation();
	FRotator RotatorTrigger = this->TriggerKey->GetActorRotation();
	UStaticMeshComponent * temp = this->Key->FindComponentByClass<UStaticMeshComponent>();
	temp->SetSimulatePhysics(false);
	this->Key->SetActorLocation(LocationTrigger);
	this->Key->SetActorRotation(RotatorTrigger);
}
