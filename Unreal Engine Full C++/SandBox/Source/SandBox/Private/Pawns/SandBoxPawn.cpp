// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/SandBoxPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandBoxPawn, All, All)

// Sets default values
ASandBoxPawn::ASandBoxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create scene component
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene component");
	SetRootComponent(this->SceneComponent);

	//Create Static Mesh Component
	this->StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	this->StaticMeshComp->SetupAttachment(GetRootComponent());

	//Create Camera Component
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	this->CameraComp->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void ASandBoxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASandBoxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		this->VelocityVector = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void ASandBoxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandBoxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ASandBoxPawn::MoveRight);
	}
}

void ASandBoxPawn::MoveForward(float Amount)
{
	VelocityVector.X = Amount;
}

void ASandBoxPawn::MoveRight(float Amount)
{
	VelocityVector.Y = Amount;
}

void ASandBoxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!NewController) return;
	UE_LOG(LogSandBoxPawn, Warning, TEXT("%s PossessBy: %s"), *GetName(), *NewController->GetName());
}

void ASandBoxPawn::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogSandBoxPawn, Warning, TEXT("%s Un Prossessed"), *GetName());
}
