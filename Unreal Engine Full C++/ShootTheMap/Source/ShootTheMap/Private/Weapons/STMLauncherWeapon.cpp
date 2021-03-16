// ShootTheMap


#include "Weapons/STMLauncherWeapon.h"
#include "Weapons/STMProjectile.h"
//#include "Kismet/GameplayStatics.h"

void ASTMLauncherWeapon::StartFire()
{
    this->MakeShot();
}

void ASTMLauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
        return;

    FVector TraceStart;
    FVector TraceEnd;

    if (!this->GetTraceData(TraceStart, TraceEnd))
        return;

    FHitResult HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
                                         CollisionQueryParams);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASTMProjectile *Projectile = GetWorld()->SpawnActorDeferred<ASTMProjectile>(this->ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    /* auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), this->ProjectileClass, SpawnTransform);*/
    //set projectile params
    /*UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);*/
}