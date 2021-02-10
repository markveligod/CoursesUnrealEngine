// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

private:
	float Reach = 100.f;
	bool bDebugLine = false;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;

	UInputComponent * InputComponent = nullptr;
	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	AActor * HitActor = nullptr;
	
	void RunDebugLine();
	void SetupInputComponent();
	void SetupDebugBool();
	FHitResult FindHitObject();
	void FindPhisicsHandle();
	void GiveObject();
	void PushObject();
};
