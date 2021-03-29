// ShootTheMap

#include "Characters/STMBaseCharacter.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/STMCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
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

    // Create Health component
    this->Health = CreateDefaultSubobject<UHealthComponent>("Health Component");

    //Create Weapon component
    this->WeaponComp = CreateDefaultSubobject<USTMWeaponComponent>("Weapon Component");
}

// Called when the game starts or when spawned
void ASTMBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(this->Health);
    check(GetCharacterMovement());
    //check(this->WeaponComp);
    check(GetMesh());

    this->OnHealthChanged(this->Health->GetHealth(), 0.f);
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

bool ASTMBaseCharacter::IsRunning() const
{
    return (false);
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

void ASTMBaseCharacter::SetPlayerColor(const FLinearColor &Color)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInstance)
        return;

    MaterialInstance->SetVectorParameterValue(this->MaterialColorName, Color);
}


void ASTMBaseCharacter::OnDeath()
{
    UE_LOG(LogCharacter, Warning, TEXT("Player %s is Dead!"), *GetName());
    //PlayAnimMontage(this->DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SetLifeSpan(5.f);
    this->WeaponComp->StopFire();
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASTMBaseCharacter::OnHealthChanged(float NewHealth, float HealthDelta)
{
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
