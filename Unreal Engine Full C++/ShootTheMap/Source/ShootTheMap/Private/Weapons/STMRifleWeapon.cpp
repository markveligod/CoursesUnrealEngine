// ShootTheMap


#include "Weapons/STMRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "STMWeaponVFXComponent.h"


ASTMRifleWeapon::ASTMRifleWeapon()
{
    this->WeaponVFXComponent = CreateDefaultSubobject<USTMWeaponVFXComponent>("Weapon VFX Component");
}

void ASTMRifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(this->WeaponVFXComponent);
}

void ASTMRifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(this->ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
    this->MakeShot();
}

void ASTMRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(this->ShotTimerHandle);
}

void ASTMRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        this->StopFire();
        return;
    }

    FVector TraceStart;
    FVector TraceEnd;

    if (!this->GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    CollisionQueryParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                         CollisionQueryParams);
    this->MakeHit(HitResult, TraceStart, TraceEnd);
    DecreaseAmmo();
}

bool ASTMRifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!this->GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;
    TraceStart = ViewLocation; /*SocketTrans.GetLocation();*/
    const auto HalfRad = FMath::DegreesToRadians(this->BulletSpreed);
    const FVector ShootDirection =
        FMath::VRandCone(ViewRotation.Vector(), HalfRad); /*SocketTrans.GetRotation().GetForwardVector();*/
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return (true);
}

void ASTMRifleWeapon::MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd)
{
    if (HitResult.bBlockingHit)
    {
        //DrawDebugLine(GetWorld(), this->GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.f, 0,3.f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.f);
        this->MakeDamage(HitResult);
        this->WeaponVFXComponent->PlayImpact(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), this->GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.f, 0, 3.f);
    }
}

void ASTMRifleWeapon::MakeDamage(FHitResult &HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor)
        return;
    DamageActor->TakeDamage(this->DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
