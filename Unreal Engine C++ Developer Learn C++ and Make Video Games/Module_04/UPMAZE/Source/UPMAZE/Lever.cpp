// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerController.h"
#include "Lever.h"


// Sets default values for this component's properties
ULever::ULever()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void ULever::BeginPlay()
{
	if (this->Trigger && this->CurrentCharacter && this->Door)
	{
		Super::BeginPlay();

		//установка компонентам Movable
		this->ComponentDoor = this->Door->FindComponentByClass<UStaticMeshComponent>();
		this->ComponentDoor->SetMobility(EComponentMobility::Movable);
		GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMobility(EComponentMobility::Movable);
		
		UE_LOG(LogTemp, Warning, TEXT("Компонент => %s"), *this->ComponentDoor->GetName())
		UE_LOG(LogTemp, Warning, TEXT("Установлен триггер персонаж и дверь для рычага!"))
		
		ComponentTemp = this->CurrentCharacter->FindComponentByClass<UInputComponent>();
		if (ComponentTemp)
		{
			UE_LOG(LogTemp, Warning, TEXT("У него есть компоненты!"));
			ComponentTemp->BindAction("KeyE", IE_Pressed, this, &ULever::Down);
		}
		//Компоненты ротатора двери
		this->DoorRotator = this->Door->GetActorRotation();
		this->StartYawDoor = this->DoorRotator.Yaw;
		this->CurrYawDoor = this->StartYawDoor;
		this->EndYawDoor += this->StartYawDoor;

		//Компоненты ротатора рычага
		this->LeverRotator = GetOwner()->GetActorRotation();
		this->StartPitchLever = this->LeverRotator.Pitch;
		this->CurrPitchLever = this->StartPitchLever;
		this->EndPitchLever += this->StartPitchLever;
		UE_LOG(LogTemp, Warning, TEXT("CurrRoll: %s\nEndRoll: %s"), *(FString(FString::SanitizeFloat(this->CurrPitchLever ))), *(FString (FString::SanitizeFloat(this->EndPitchLever))));
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Не установлен триггер персонаж или дверь для рычага !"))
	
}


// Called every frame
void ULever::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->bRunDownLever && this->CurrPitchLever < this->EndPitchLever - 5.f)
	{
		this->DownTheLever(DeltaTime);
		if (this->CurrPitchLever >= this->EndPitchLever - 5.f)
			this->bRunOpenTheDoor = true;
	}

	if (this->bRunOpenTheDoor && this->CurrYawDoor < this->EndYawDoor - 5.f)
	{
		this->OpenTheDoor(DeltaTime);
	}

}

void ULever::Down()
{
	
	if (this->Trigger->IsOverlappingActor(this->CurrentCharacter) && this->bPressE == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Down done!"));
		this->bPressE = true;
		this->bRunDownLever = true;
	}
}

void ULever::DownTheLever(float delta)
{
	float TempCurrPitch = this->CurrPitchLever;
	this->CurrPitchLever = FMath::Lerp(TempCurrPitch, this->EndPitchLever, 5.f * delta);
	GetOwner()->SetActorRotation(FRotator(this->CurrPitchLever, this->LeverRotator.Yaw, this->LeverRotator.Roll));
}

void ULever::OpenTheDoor(float delta)
{
	float TempCurrYaw = this->StartYawDoor + this->CurrYawDoor;
	this->CurrYawDoor = FMath::Lerp(TempCurrYaw, this->EndYawDoor, this->PowerOpenDoor * delta);
	this->Door->SetActorRotation(FRotator(this->DoorRotator.Pitch, this->CurrYawDoor, this->DoorRotator.Roll));
}

bool ULever::IsRunDownLever() { return (this->bRunOpenTheDoor);}
