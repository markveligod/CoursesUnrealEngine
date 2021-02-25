// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "ComponentHandle.h"

// Sets default values for this component's properties
UComponentHandle::UComponentHandle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComponentHandle::BeginPlay()
{
	Super::BeginPlay();

	this->PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (this->PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle find"));
		this->ComponentInputTemp = GetOwner()->FindComponentByClass<UInputComponent>();
		if (this->ComponentInputTemp)
		{
			UE_LOG(LogTemp, Warning, TEXT("ComponentInputTemp find"));
			this->bDoneHandle = true;
			this->ComponentInputTemp->BindAction("KeyE", IE_Pressed, this, &UComponentHandle::GiveObject);
			this->ComponentInputTemp->BindAction("KeyE", IE_Released, this, &UComponentHandle::PushObject);
		}
	}
}


// Called every frame
void UComponentHandle::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->bDoneHandle)
	{
		//UE_LOG(LogTemp, Warning, TEXT("bDoneHandle done"));
		FHitResult Hit = FindHitObject();
		this->ComponentToGrab = Hit.GetComponent();
		this->HitActor = Hit.GetActor();
		// if (this->HitActor)
		// 	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *this->HitActor->GetName())
		if (this->PhysicsHandle->GrabbedComponent)
		{
			this->PhysicsHandle->SetTargetLocation(this->GrabLocaction);
		}
	}

}

FHitResult UComponentHandle::FindHitObject()
{
	FVector start;
	FRotator direction;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(start, direction);
	this->GrabLocaction = start + direction.Vector() * this->Distance;
	FHitResult Hit;
	FCollisionQueryParams Params(FName(TEXT("param")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(Hit, start, this->GrabLocaction, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), Params);
	//DrawDebugLine(GetWorld(), start, this->GrabLocaction, FColor(250, 0, 0), false, 0.f, 0, 5.f);
	return (Hit);
}

void UComponentHandle::GiveObject()
{
	if (this->HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pressed E"));
		this->PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, FName(TEXT("Grab")), this->GrabLocaction);
	}
}

void UComponentHandle::PushObject()
{
	UE_LOG(LogTemp, Warning, TEXT("Release E"));
	this->PhysicsHandle->ReleaseComponent();
}
