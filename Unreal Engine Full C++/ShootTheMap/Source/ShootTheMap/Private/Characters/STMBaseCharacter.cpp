// ShootTheMap

#include "Characters/STMBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/STMCharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/STMWeaponComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogCharacter, All, All)

// Sets default values
ASTMBaseCharacter::ASTMBaseCharacter(const FObjectInitializer &ObjInit)
    : Super(
          ObjInit.SetDefaultSubobjectClass<USTMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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

    // Create Health component
    this->Health = CreateDefaultSubobject<UHealthComponent>("Health Component");

    this->HealthTextComp = CreateDefaultSubobject<UTextRenderComponent>("Text Health Component");
    this->HealthTextComp->SetupAttachment(GetRootComponent());
    this->HealthTextComp->bOwnerNoSee = true;

    //Create Weapon component
    this->WeaponComp = CreateDefaultSubobject<USTMWeaponComponent>("Weapon Component");
}

// Called when the game starts or when spawned
void ASTMBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(this->Health);
    check(this->HealthTextComp);
    check(GetCharacterMovement());
    check(this->WeaponComp);
    check(GetMesh());

    this->OnHealthChanged(this->Health->GetHealth());
    this->Health->OnDeath.AddUObject(this, &ASTMBaseCharacter::OnDeath);
    this->Health->OnDeathChange.AddUObject(this, &ASTMBaseCharacter::OnHealthChanged);

    //Join to delegate LandedDelegate
    LandedDelegate.AddDynamic(this, &ASTMBaseCharacter::OnGroundLanded);

    
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
    if (PlayerInputComponent)
    {
        PlayerInputComponent->BindAxis("MoveForward", this, &ASTMBaseCharacter::MoveForward);
        PlayerInputComponent->BindAxis("MoveRight", this, &ASTMBaseCharacter::MoveRight);
        PlayerInputComponent->BindAxis("LookUp", this, &ASTMBaseCharacter::AddControllerPitchInput);
        PlayerInputComponent->BindAxis("TurnAround", this, &ASTMBaseCharacter::AddControllerYawInput);
        PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTMBaseCharacter::Jump);
        PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTMBaseCharacter::StartRun);
        PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTMBaseCharacter::StopRun);
        PlayerInputComponent->BindAction("Fire", IE_Pressed, this->WeaponComp, &USTMWeaponComponent::StartFire);
        PlayerInputComponent->BindAction("Fire", IE_Released, this->WeaponComp, &USTMWeaponComponent::StopFire);
        PlayerInputComponent->BindAction("NextWeapon", IE_Released, this->WeaponComp, &USTMWeaponComponent::NextWeapon);
        PlayerInputComponent->BindAction("Reload", IE_Pressed, this->WeaponComp, &USTMWeaponComponent::Reload);

    }
}

bool ASTMBaseCharacter::IsRunning() const
{
    return (this->bIsMovingFrw && this->bRunAction && !GetVelocity().IsZero());
}

float ASTMBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return (0.0f);
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return (CrossProduct.IsZero() ? Degrees : FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z));
}

void ASTMBaseCharacter::MoveForward(float amount)
{
    this->bIsMovingFrw = amount > 0.0f;
    if (amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), amount);
}

void ASTMBaseCharacter::MoveRight(float amount)
{
    if (amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), amount);
}

void ASTMBaseCharacter::StartRun()
{
    this->bRunAction = true;
}

void ASTMBaseCharacter::StopRun()
{
    this->bRunAction = false;
}

void ASTMBaseCharacter::OnDeath()
{
    UE_LOG(LogCharacter, Warning, TEXT("Player %s is Dead!"), *GetName());
    //PlayAnimMontage(this->DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SetLifeSpan(5.f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    this->WeaponComp->StopFire();
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASTMBaseCharacter::OnHealthChanged(float NewHealth)
{
    this->HealthTextComp->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}

void ASTMBaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    const auto FallVelocity = -GetCharacterMovement()->Velocity.Z;
    if (FallVelocity < LandedDamageVelocity.X)
        return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandeDamage, FallVelocity);
    UE_LOG(LogCharacter, Warning, TEXT("Final Damage: %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}



// void ASTMBaseCharacter::LookUp(float amount)
//{
//    AddControllerPitchInput(amount);
//}
//
// void ASTMBaseCharacter::TurnAround(float amount)
//{
//    AddControllerYawInput(amount);
//}
