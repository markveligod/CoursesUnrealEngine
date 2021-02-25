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

//===========================
// RunDebugLine - рисует линии вокруг пешки
//===========================
void UGrabber::RunDebugLine()
{
	const float Delay = 30.f;
	const float MaxRotation = 360.f;

	for (float temp_pitch = 0.f; temp_pitch < MaxRotation; temp_pitch += Delay)
	{
		FVector LineTraceEndTemp = this->PlayerViewPointLocation + (this->PlayerViewPointRotation + FRotator(temp_pitch, 0.f, 0.f)).Vector() * this->Reach;
		DrawDebugLine(GetWorld(), this->PlayerViewPointLocation, LineTraceEndTemp, FColor(0, 255, 0), false, 0.f, 0, 5.f);
	}

	for (float temp_yaw = 0.f; temp_yaw < MaxRotation; temp_yaw += Delay)
	{
		FVector LineTraceEndTemp = this->PlayerViewPointLocation + (this->PlayerViewPointRotation + FRotator(0.f, temp_yaw, 0.f)).Vector() * this->Reach;
		DrawDebugLine(GetWorld(), this->PlayerViewPointLocation, LineTraceEndTemp, FColor(0, 255, 0), false, 0.f, 0, 5.f);
	}
}

void UGrabber::SetupDebugBool() {this->bDebugLine = (this->bDebugLine == true) ?  false : true;}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GRABBER START BEGIN!!!"));
	this->SetupInputComponent();
	this->FindPhisicsHandle();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//получение позиции игрока
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(this->PlayerViewPointLocation, this->PlayerViewPointRotation);
	this->LineTraceEnd = this->PlayerViewPointLocation + this->PlayerViewPointRotation.Vector() * this->Reach;
	if (this->PhysicsHandle->GrabbedComponent)
	{
		this->PhysicsHandle->SetTargetLocation(this->LineTraceEnd);
	}

	//рисуем дебаг линии вокруг персонажа по нажатии К
	if (this->bDebugLine)
		this->RunDebugLine();
}

void UGrabber::GiveObject()
{
	UE_LOG(LogTemp, Warning, TEXT("Button E Pressed!"));

	FHitResult Hit = this->FindHitObject();
	UPrimitiveComponent *ComponentToGrab = Hit.GetComponent();

	if (this->HitActor)
	{
		this->PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, this->LineTraceEnd);
	}
}

void UGrabber::PushObject()
{
	UE_LOG(LogTemp, Warning, TEXT("Button E Released!"));
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetupInputComponent()
{
	this->InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (this->InputComponent)
	{
		this->InputComponent->BindAction("Debug", IE_Pressed, this, &UGrabber::SetupDebugBool);
		this->InputComponent->BindAction("GiveObj", IE_Pressed, this, &UGrabber::GiveObject);
		this->InputComponent->BindAction("GiveObj", IE_Released, this, &UGrabber::PushObject);
	}
}

void UGrabber::FindPhisicsHandle()
{
	this->PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (this->PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle finded: %s"), *(this->PhysicsHandle->GetName()));
	}
}

FHitResult UGrabber::FindHitObject()
{
	FHitResult Hit;
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(Hit, this->PlayerViewPointLocation, this->LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParam);

	this->HitActor = Hit.GetActor();
	if (this->HitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AActor finded: %s"), *(this->HitActor->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AActor not found!"));
	}
	return (Hit);
}
