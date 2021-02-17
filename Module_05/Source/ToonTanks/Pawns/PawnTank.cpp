// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

APawnTank::APawnTank()
{
    this->ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    this->ArmComponent->SetupAttachment(RootComponent);

    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    this->CameraComponent->SetupAttachment(this->ArmComponent);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

    this->PlayerControllerRef = Cast<APlayerController>(this->GetController());
}

void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
    // Hide player
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    this->Move();
    this->Rotate();

    if (this->PlayerControllerRef)
    {
        FHitResult TraceHitResult;
        this->PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        Super::RotateTurrentFunction(HitLocation);
    }
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
    // PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APawnTank::BeginCrouch);
    // PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APawnTank::LeaveCrouch);
}

void APawnTank::CalculateMoveInput(float value) 
{
    this->MoveDirection = FVector(value * this->MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float value) 
{
    float RotateAmount = value * this->RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    this->RotationDirection = FQuat(Rotation);
}

void APawnTank::Move() 
{
    AddActorLocalOffset(this->MoveDirection, true);
}

void APawnTank::Rotate() 
{
    AddActorLocalRotation(this->RotationDirection, true);
}
