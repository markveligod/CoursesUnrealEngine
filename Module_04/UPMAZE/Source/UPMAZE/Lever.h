// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Lever.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPMAZE_API ULever : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULever();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsRunDownLever();

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume *Trigger = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *CurrentCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	AActor *Door;

	UPROPERTY(EditAnywhere)
	float EndYawDoor = 90.f;

	UPROPERTY(EditAnywhere)
	float PowerOpenDoor = 0.5f;

	//данные для двери
	FRotator DoorRotator;
	float StartYawDoor;
	float CurrYawDoor;

	//данные для движения рычага
	FRotator LeverRotator;
	float StartPitchLever;
	float CurrPitchLever;
	float EndPitchLever = 80.f;

	//компонент действия
	UInputComponent * ComponentTemp;

	//Булевые переключатели
	bool bPressE = false;
	bool bRunDownLever = false;
	bool bRunOpenTheDoor = false;

	//Функции для выполнения действий
	void Down();
	void OpenTheDoor(float delta);
	void DownTheLever(float delta);
	

	//получение компонента двери
	UStaticMeshComponent * ComponentDoor;

};
