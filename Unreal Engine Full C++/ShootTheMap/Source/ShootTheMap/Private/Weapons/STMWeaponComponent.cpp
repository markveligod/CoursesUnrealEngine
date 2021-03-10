// ShootTheMap

#include "Weapons/STMWeaponComponent.h"
#include "Characters/STMBaseCharacter.h"
#include "GameFramework/Character.h"
#include "Weapons/STMBaseWeapon.h"

// Sets default values for this component's properties
USTMWeaponComponent::USTMWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTMWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    this->SpawnWeapons();
    this->EquipWeapon(this->CurrentIndexWeapon);
}

void USTMWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    this->CurrentWeapon = nullptr;
    for (auto WeaponPtr : this->WeaponsPtr)
    {
        WeaponPtr->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        WeaponPtr->Destroy();
    }
    this->WeaponsPtr.Empty();
    Super::EndPlay(EndPlayReason);
}


void USTMWeaponComponent::SpawnWeapons()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (auto WeaponClass : this->WeaponClasses)
    {
        auto TempWeapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(WeaponClass);
        if (!TempWeapon)
            continue;
        TempWeapon->SetOwner(GetOwner());
        this->WeaponsPtr.Add(TempWeapon);

        AttachWeaponToSocket(TempWeapon, Character->GetMesh(), this->WeaponArmorySocketName);
    }

    
}

void USTMWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    if (this->CurrentWeapon)
    {
        this->CurrentWeapon->StopFire();
        AttachWeaponToSocket(this->CurrentWeapon, Character->GetMesh(), this->WeaponArmorySocketName);
    }

    this->CurrentWeapon = this->WeaponsPtr[WeaponIndex];
    AttachWeaponToSocket(this->CurrentWeapon, Character->GetMesh(), this->WeaponEquipSocketName);
}

void USTMWeaponComponent::AttachWeaponToSocket(ASTMBaseWeapon *Weapon, USceneComponent *Mesh, const FName& Socket)
{
    if (!Weapon || !Mesh)
        return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Mesh, AttachmentRules, Socket);
}

void USTMWeaponComponent::StartFire()
{
    if (!this->CurrentWeapon)
        return;

    this->CurrentWeapon->StartFire();
}

void USTMWeaponComponent::StopFire()
{
    if (!this->CurrentWeapon)
        return;

    this->CurrentWeapon->StopFire();
}

void USTMWeaponComponent::NextWeapon()
{
    this->CurrentIndexWeapon = (CurrentIndexWeapon + 1) % this->WeaponsPtr.Num();
    this->EquipWeapon(this->CurrentIndexWeapon);
}
