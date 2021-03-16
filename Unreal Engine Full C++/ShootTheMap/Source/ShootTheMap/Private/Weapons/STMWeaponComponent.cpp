// ShootTheMap

#include "Weapons/STMWeaponComponent.h"
#include "Characters/STMBaseCharacter.h"
#include "GameFramework/Character.h"
#include "Weapons/STMBaseWeapon.h"
#include "Notifys/STMEquipFinishAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

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
    this->InitAnimations();
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

    for (auto Data : this->WeaponDates)
    {
        auto TempWeapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(Data.WeaponClass);
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
    this->AnimInProgress = true;
    this->AnimEquip(this->AnimationEquip);
}

void USTMWeaponComponent::AnimEquip(UAnimMontage *Animation)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
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
    if (!this->CanFire())
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
    if (!this->CanEquip())
        return;
    this->CurrentIndexWeapon = (CurrentIndexWeapon + 1) % this->WeaponsPtr.Num();
    this->EquipWeapon(this->CurrentIndexWeapon);
}

void USTMWeaponComponent::InitAnimations()
{
    if (!this->AnimationEquip)
        return;

    const auto NotifyEvents = this->AnimationEquip->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishNotify = Cast<USTMEquipFinishAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishNotify)
        {
            EquipFinishNotify->OnNotifySignature.AddUObject(this, &USTMWeaponComponent::OnEquipFinish);
            break;
        }
    }
}

void USTMWeaponComponent::OnEquipFinish(USkeletalMeshComponent *Mesh)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != Mesh)
        return;

    this->AnimInProgress = false;
    UE_LOG(LogWeaponComponent, Warning, TEXT("Finished equip"));
}

bool USTMWeaponComponent::CanFire() const
{
    return (CurrentWeapon && !this->AnimInProgress);
}

bool USTMWeaponComponent::CanEquip() const
{
    return (!this->AnimInProgress);
}
