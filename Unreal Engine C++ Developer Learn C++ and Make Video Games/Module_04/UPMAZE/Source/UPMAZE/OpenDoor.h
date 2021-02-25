// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPMAZE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume *TriggerKey = nullptr;

	UPROPERTY(EditAnywhere)
	AActor * Key = nullptr;

	UPROPERTY(EditAnywhere)
	AActor * Character = nullptr;

	UPROPERTY(EditAnywhere)
	float DistTheDoor = 80.f;

	UPROPERTY(EditAnywhere)
	float PowerTheDoor = 0.5f;


	float StartLocalTheDoor;
	float TempLocalTheDoor;
	float EndLocalTheDoor;

	bool bOpenStart = false;
	UPhysicsHandleComponent * PhysicsHandle = nullptr;

	void SetupKey();
	void StartOpenTheDoor(float delta);

};
