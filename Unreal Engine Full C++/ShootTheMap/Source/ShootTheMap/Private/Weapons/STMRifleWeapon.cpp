// ShootTheMap

#include "Weapons/STMRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "STMWeaponVFXComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/STMPlayerCharacter.h"

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
    const auto StmCharacter = Cast<ASTMPlayerCharacter>(GetOwner());
    if (StmCharacter && StmCharacter->IsRunning())
    {
        return;
    }
    this->InitFX();
    GetWorldTimerManager().SetTimer(this->ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
    this->MakeShot();
}

void ASTMRifleWeapon::StopFire()
{
    this->SetFXActive(false);
    GetWorldTimerManager().ClearTimer(this->ShotTimerHandle);
}

void ASTMRifleWeapon::MakeShot()
{
    const auto StmCharacter = Cast<ASTMPlayerCharacter>(GetOwner());

    if (!GetWorld() || IsAmmoEmpty() || (StmCharacter && StmCharacter->IsRunning()))
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
    this->SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
}

void ASTMRifleWeapon::InitFX()
{
    if (!this->MuzzleFXComponent)
    {
        this->MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!this->AudioComponent)
    {
        this->AudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, this->WeaponMesh, MuzzleSocketName);
    }
    this->SetFXActive(true);
}

void ASTMRifleWeapon::SetFXActive(bool IsActive)
{
    if (this->MuzzleFXComponent)
    {
        this->MuzzleFXComponent->SetPaused(!IsActive);
        this->MuzzleFXComponent->SetVisibility(IsActive, true);
    }
    if (this->AudioComponent)
    {
        IsActive ? this->AudioComponent->Play() : this->AudioComponent->Stop();
    }
}

void ASTMRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
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
    DamageActor->TakeDamage(this->DamageAmount, FDamageEvent{}, GetController(), this);
}

AController *ASTMRifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return (Pawn ? Pawn->GetController() : nullptr);
}
