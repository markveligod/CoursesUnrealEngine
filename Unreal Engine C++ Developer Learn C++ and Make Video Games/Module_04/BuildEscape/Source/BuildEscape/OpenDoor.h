// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDESCAPE_API UOpenDoor : public UActorComponent
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
	float RollValue = 88.f;
	float TargetStartYaw;
	float TargetEndYaw;
	FRotator OpenDoor;
	bool OpenDoorSound = true;
	bool CloseDoorSound = true;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *ActorPawn = nullptr;

	float DoorLastOpen = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float SpeedOpenCloseDoor = 0.8f;
	
	UPROPERTY(EditAnywhere)
	float MassDoor = 50.f;

	UPROPERTY(EditAnywhere)
	AActor * Key = nullptr;

	UPROPERTY()
	UAudioComponent * AudioComp = nullptr;
	
	void OpenDoorRun(float DeltaTime);
	void CloseDoorRun(float DeltaTime);
	float TotalMassOfActor() const;

	bool CheckStartFunc() const;

	void FindAudioComponent();
	
};
