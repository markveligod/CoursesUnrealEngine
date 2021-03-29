// ShootTheMap


#include "Characters/STMPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/STMWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"


ASTMPlayerCharacter::ASTMPlayerCharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;

    // Create Spring Arm Component
    this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
    this->SpringArm->SetupAttachment(GetRootComponent());
    this->SpringArm->bUsePawnControlRotation = true;
    this->SpringArm->SocketOffset = FVector(0.f, 100.f, 80.f);

    // Create Camera Component
    this->CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
    this->CameraComponent->SetupAttachment(this->SpringArm);

    //Camera Collision
    this->CameraCollision = CreateDefaultSubobject<USphereComponent>("Sphere Component");
    this->CameraCollision->SetupAttachment(this->CameraComponent);
    this->CameraCollision->SetSphereRadius(10.f);
    this->CameraCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASTMPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(this->CameraCollision);

    this->CameraCollision->OnComponentBeginOverlap.AddDynamic(this,
                                                              &ASTMPlayerCharacter::OnCameraCollisionBeginOverlap);
    this->CameraCollision->OnComponentEndOverlap.AddDynamic(this,
                                                              &ASTMPlayerCharacter::OnCameraCollisionEndOverlap);

}

// Called to bind functionality to input
void ASTMPlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASTMPlayerCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &ASTMPlayerCharacter::MoveRight);
        PlayerInputComponent->BindAxis("LookUp", this, &ASTMPlayerCharacter::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("TurnAround", this, &ASTMPlayerCharacter::AddControllerYawInput);
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTMPlayerCharacter::Jump);
        PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTMPlayerCharacter::StartRun);
        PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTMPlayerCharacter::StopRun);
        PlayerInputComponent->BindAction("Fire", IE_Pressed, this->WeaponComp, &USTMWeaponComponent::StartFire);
        PlayerInputComponent->BindAction("Fire", IE_Released, this->WeaponComp, &USTMWeaponComponent::StopFire);
        PlayerInputComponent->BindAction("NextWeapon", IE_Released, this->WeaponComp, &USTMWeaponComponent::NextWeapon);
        PlayerInputComponent->BindAction("Reload", IE_Pressed, this->WeaponComp, &USTMWeaponComponent::Reload);
    }
}

bool ASTMPlayerCharacter::IsRunning() const
{
    return (this->bIsMovingFrw && this->bRunAction && !GetVelocity().IsZero());
}

void ASTMPlayerCharacter::MoveForward(float amount)
{
    this->bIsMovingFrw = amount > 0.0f;
    if (amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), amount);
}

void ASTMPlayerCharacter::MoveRight(float amount)
{
    if (amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), amount);
}

void ASTMPlayerCharacter::StartRun()
{
    this->bRunAction = true;
}

void ASTMPlayerCharacter::StopRun()
{
    this->bRunAction = false;
}

void ASTMPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult &SweepResult)
{
    this->CheckCameraOverlap();
}

void ASTMPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    this->CheckCameraOverlap();
}

void ASTMPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTMPlayerCharacter::CheckCameraOverlap()
{
    const auto HideMesh = this->CameraCollision->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);
}

