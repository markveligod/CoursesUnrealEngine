// ShootTheMap

#include "Weapons/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTMBaseWeapon::ASTMBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    this->WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
    SetRootComponent(this->WeaponMesh);
}

void ASTMBaseWeapon::StartFire()
{
    
}

void ASTMBaseWeapon::StopFire()
{

}

void ASTMBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(this->WeaponMesh);
    checkf(this->DefaultAmmoData.Bullet > 0, TEXT("Bullet < 0"));
    checkf(this->DefaultAmmoData.Clips > 0, TEXT("Clips < 0"));
    this->CurrentAmmo = this->DefaultAmmoData; 
}

void ASTMBaseWeapon::MakeShot()
{

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

void ASTMBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullet == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("Bullet == 0"));
        return;
    }

    this->CurrentAmmo.Bullet--;
    this->LogAmmo();

    if (this->IsClipEmpty() && !this->IsAmmoEmpty())
    {
        //StopFire();
        this->OnClimpEmptySignature.Broadcast(this);
    }
}

bool ASTMBaseWeapon::IsAmmoEmpty() const
{
    return (!this->CurrentAmmo.bInfinity && this->CurrentAmmo.Clips == 0 && this->IsClipEmpty());
}

bool ASTMBaseWeapon::IsClipEmpty() const
{
    return (this->CurrentAmmo.Bullet == 0);
}

void ASTMBaseWeapon::ChangeClip()
{
    if (!this->CurrentAmmo.bInfinity)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogBaseWeapon, Warning, TEXT("Clips == 0"));
            return;
        }
        this->CurrentAmmo.Clips--;
    }
    this->CurrentAmmo.Bullet = this->DefaultAmmoData.Bullet;
    UE_LOG(LogBaseWeapon, Warning, TEXT("---Change Clip---"));
}

bool ASTMBaseWeapon::CanReload() const
{
    return (this->CurrentAmmo.Bullet < this->DefaultAmmoData.Bullet && this->CurrentAmmo.Clips > 0);
}

FWeaponUIData ASTMBaseWeapon::GetUIData() const
{
    return (this->UIData);
}

FAmmoData ASTMBaseWeapon::GetAmmoData() const
{
    return (this->CurrentAmmo);
}

bool ASTMBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if (this->CurrentAmmo.bInfinity || this->IsAmmoFull() || ClipsAmount <= 0)
        return (false);

    if (IsAmmoEmpty())
    {
        UE_LOG(LogBaseWeapon, Display, TEXT("Actor: %s => Ammo is Empty"), *GetOwner()->GetName());
        this->CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, this->DefaultAmmoData.Clips + 1);
        this->OnClimpEmptySignature.Broadcast(this);
    }
    else if (this->CurrentAmmo.Clips < this->DefaultAmmoData.Clips)
    {
        const auto NextClips = this->CurrentAmmo.Clips + ClipsAmount;
        if (this->DefaultAmmoData.Clips - NextClips >= 0)
        {
            this->CurrentAmmo.Clips = NextClips;
            UE_LOG(LogBaseWeapon, Display, TEXT("Actor: %s => (NextClips >= 0)"), *GetOwner()->GetName());
        }
        else
        {
            this->CurrentAmmo.Clips = this->DefaultAmmoData.Clips;
            this->CurrentAmmo.Bullet = this->DefaultAmmoData.Bullet;
            UE_LOG(LogBaseWeapon, Display, TEXT("Actor: %s => Ammo is full"), *GetOwner()->GetName());
        }
    }
    else
    {
        this->CurrentAmmo.Bullet = this->DefaultAmmoData.Bullet;
        UE_LOG(LogBaseWeapon, Display, TEXT("Actor: %s => Clips is full"), *GetOwner()->GetName());
    }
    return (true);
}

void ASTMBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(this->CurrentAmmo.Bullet) + "/";
    AmmoInfo += (this->CurrentAmmo.bInfinity ? "Infinity" : FString::FromInt(this->CurrentAmmo.Clips));
    UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *AmmoInfo);

}

bool ASTMBaseWeapon::IsAmmoFull() const
{
    return (this->CurrentAmmo.Clips == this->DefaultAmmoData.Clips && this->CurrentAmmo.Bullet == this->DefaultAmmoData.Bullet);
}

UNiagaraComponent * ASTMBaseWeapon::SpawnMuzzleFX()
{
    return (UNiagaraFunctionLibrary::SpawnSystemAttached(this->MuzzleFX,   //
                                                 this->WeaponMesh, //
                                                 this->MuzzleSocketName,//
        FVector::ZeroVector,//
        FRotator::ZeroRotator,//
        EAttachLocation::SnapToTarget,//
        true));
}




