// ShootTheMap

#include "Weapons/STMRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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
    this->InitMuzzleFX();
    GetWorldTimerManager().SetTimer(this->ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
    this->MakeShot();
}

void ASTMRifleWeapon::StopFire()
{
    this->SetMuzzleVisibility(false);
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
    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        this->MakeDamage(HitResult);
        this->WeaponVFXComponent->PlayImpact(HitResult);
    }
    UE_LOG(LogTemp, Display, TEXT("Trace End %s"), *TraceEnd.ToString());
    UE_LOG(LogTemp, Display, TEXT("TRace FX %s"), *TraceFXEnd.ToString());
    this->SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
}

void ASTMRifleWeapon::InitMuzzleFX()
{
    if (!this->MuzzleFXComponent)
    {
        this->MuzzleFXComponent = SpawnMuzzleFX();
    }
    this->SetMuzzleVisibility(true);
}

void ASTMRifleWeapon::SetMuzzleVisibility(bool Visible)
{
    if (this->MuzzleFXComponent)
    {
        this->MuzzleFXComponent->SetPaused(!Visible);
        this->MuzzleFXComponent->SetVisibility(Visible, true);
    }
}

void ASTMRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    UE_LOG(LogTemp, Display, TEXT("Trace End in function %s"), *TraceEnd.ToString());
    UE_LOG(LogTemp, Display, TEXT("TRace Start Muzzle socket %s"), *TraceStart.ToString());
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation( //
        GetWorld(),                                                               //
        this->TraceFX,                                                            //
        TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(this->TraceTargetName, TraceEnd);
    }
}

void ASTMRifleWeapon::MakeDamage(FHitResult &HitResult)
{
    const auto DamageActor = HitResult.GetActor();
    if (!DamageActor)
        return;
    DamageActor->TakeDamage(this->DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
