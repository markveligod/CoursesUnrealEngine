// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GRABBER START BEGIN!!!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// Get players viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	// UE_LOG(LogTemp, Warning, TEXT("\nLocation: %s \nRotator: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	//draw debug line

	this->RunDebugLine(PlayerViewPointLocation, PlayerViewPointRotation);

	//ray-cast out a certain distance (Reach)
}

void UGrabber::RunDebugLine(FVector StartVec, FRotator PointRotator)
{
	const float Delay = 30.f;
	const float MaxRotation = 360.f;

	for (float temp_pitch = 0.f; temp_pitch < MaxRotation; temp_pitch += Delay)
	{
		FVector LineTraceEnd = StartVec + (PointRotator + FRotator(temp_pitch, 0.f, 0.f)).Vector() * this->Reach;
		DrawDebugLine(GetWorld(), StartVec, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);
	}

	for (float temp_yaw = 0.f; temp_yaw < MaxRotation; temp_yaw += Delay)
	{
		FVector LineTraceEnd = StartVec + (PointRotator + FRotator(0.f, temp_yaw, 0.f)).Vector() * this->Reach;
		DrawDebugLine(GetWorld(), StartVec, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f);
	}
}
