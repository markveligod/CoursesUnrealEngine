// ShootTheMap

#include "Weapons/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTMBaseWeapon::ASTMBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    this->WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
    SetRootComponent(this->WeaponMesh);
}

void ASTMBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Warning, TEXT("FIRE!!!"));
    this->MakeShot();
}

void ASTMBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(this->WeaponMesh);
}

void ASTMBaseWeapon::MakeShot()
{
    if (!GetWorld())
        return;

    FVector TraceStart;
    FVector TraceEnd;

    if (!this->GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                             CollisionQueryParams);
    this->MakeHit(HitResult, TraceStart, TraceEnd);
}

APlayerController *ASTMBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;

    return (Player->GetController<APlayerController>());
}

bool ASTMBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
    const auto Controller = this->GetPlayerController();
    if (!Controller)
        return (false);
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return (true);
}

FVector ASTMBaseWeapon::GetMuzzleWorldLocation() const
{
    return (this->WeaponMesh->GetSocketTransform(this->MuzzleSocketName).GetLocation());
}

bool ASTMBaseWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!this->GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    TraceStart = ViewLocation;              /*SocketTrans.GetLocation();*/
    const FVector ShootDirection = ViewRotation.Vector(); /*SocketTrans.GetRotation().GetForwardVector();*/
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return (true);
}

void ASTMBaseWeapon::MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd)
{
    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(), this->GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0, 3.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);

        this->MakeDamage(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), this->GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 3.f);
    }
}

void ASTMBaseWeapon::MakeDamage(FHitResult &HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor)
        return;
    DamageActor->TakeDamage(this->DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}


