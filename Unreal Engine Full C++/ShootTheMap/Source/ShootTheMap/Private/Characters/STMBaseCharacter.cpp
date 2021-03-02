// ShootTheMap

#include "Characters/STMBaseCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASTMBaseCharacter::ASTMBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;

    //Create Camera Component
    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
    this->CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTMBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASTMBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTMBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
