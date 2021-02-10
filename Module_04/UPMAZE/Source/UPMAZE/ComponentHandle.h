// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ComponentHandle.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPMAZE_API UComponentHandle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComponentHandle();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPhysicsHandleComponent * PhysicsHandle = nullptr;
	AActor * HitActor = nullptr;

	bool bDoneHandle = false;

	UPROPERTY(EditAnywhere)
	float Distance = 300.f;

	FHitResult FindHitObject();

	//компонент действия
	UInputComponent * ComponentInputTemp;

	FVector GrabLocaction;
	UPrimitiveComponent * ComponentToGrab;

	void GiveObject();
	void PushObject();
};
