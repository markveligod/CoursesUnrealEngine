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
    this->CurrentAmmo.Bullet--;
    this->LogAmmo();

    if (this->IsClipEmpty() && !this->IsAmmoEmpty())
    {
        this->ChangeClip();
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
    this->CurrentAmmo.Bullet = this->DefaultAmmoData.Bullet;
    if (!this->CurrentAmmo.bInfinity)
        this->CurrentAmmo.Clips--;
    UE_LOG(LogBaseWeapon, Warning, TEXT("---Change Clip---"));
}

void ASTMBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(this->CurrentAmmo.Bullet) + "/";
    AmmoInfo += (this->CurrentAmmo.bInfinity ? "Infinity" : FString::FromInt(this->CurrentAmmo.Clips));
    UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *AmmoInfo);

}



