// ShootTheMap

#include "Weapons/STMWeaponComponent.h"
#include "GameFramework/Character.h"
#include "Weapons/STMBaseWeapon.h"
#include "Notifys/STMEquipFinishAnimNotify.h"
#include "Notifys/STMReloadFinishAnimNotify.h"
#include "ShootTheMap/Public/Weapons/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

// Sets default values for this component's properties
USTMWeaponComponent::USTMWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTMWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(this->WeaponDates.Num() == WeaponNum, TEXT("Our character can hold only two weapon items"));

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
        TempWeapon->OnClimpEmptySignature.AddUObject(this, &USTMWeaponComponent::OnEmptyClip);
        TempWeapon->SetOwner(GetOwner());
        this->WeaponsPtr.Add(TempWeapon);

        AttachWeaponToSocket(TempWeapon, Character->GetMesh(), this->WeaponArmorySocketName);
    }

    
}

void USTMWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= this->WeaponDates.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
        return;
    }

    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    if (this->CurrentWeapon)
    {
        this->CurrentWeapon->StopFire();
        AttachWeaponToSocket(this->CurrentWeapon, Character->GetMesh(), this->WeaponArmorySocketName);
    }

    this->CurrentWeapon = this->WeaponsPtr[WeaponIndex];
    //this->CurrentReloadMontage = this->WeaponDates[WeaponIndex].AnimReload;
    const auto CurrentWeaponData = WeaponDates.FindByPredicate(
        [&](const FWeaponData &Data) { return Data.WeaponClass == CurrentWeapon->GetClass(); });
    this->CurrentReloadMontage = CurrentWeaponData ? CurrentWeaponData->AnimReload : nullptr;

    AttachWeaponToSocket(this->CurrentWeapon, Character->GetMesh(), this->WeaponEquipSocketName);
    this->EquipAnimInProgress = true;
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

void USTMWeaponComponent::Reload()
{
    this->ChangeClip();
}

bool USTMWeaponComponent::GetWeaponUIData(FWeaponUIData &UIData)
{
    if (this->CurrentWeapon)
    {
        UIData = this->CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool USTMWeaponComponent::GetAmmoUIData(FAmmoData &AmmoData) const
{
    if (this->CurrentWeapon)
    {
        AmmoData = this->CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

bool USTMWeaponComponent::TryToAddAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (auto Weapon : this->WeaponsPtr)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return (Weapon->TryToAddAmmo(ClipsAmount));
        }
    }
    return false;
}

bool USTMWeaponComponent::NeedAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType)
{
    for (auto Weapon : this->WeaponsPtr)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return (!Weapon->IsAmmoFull());
        }
    }
    return false;
}

void USTMWeaponComponent::InitAnimations()
{
    auto EquipFinishNotify = AnimUtils::FindNotifyByClass<USTMEquipFinishAnimNotify>(this->AnimationEquip);
    if (EquipFinishNotify)
    {
        EquipFinishNotify->OnNotifySignature.AddUObject(this, &USTMWeaponComponent::OnEquipFinish);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set"));
        checkNoEntry();
    }

    for (auto Weapon : this->WeaponDates)
    {
        auto ReloadFinishNotify = AnimUtils::FindNotifyByClass<USTMReloadFinishAnimNotify>(Weapon.AnimReload);
        if (!ReloadFinishNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify is forgotten to set"));
            checkNoEntry();
        }
        ReloadFinishNotify->OnNotifySignature.AddUObject(this, &USTMWeaponComponent::OnReloadFinish);
    }
}

void USTMWeaponComponent::OnEquipFinish(USkeletalMeshComponent *Mesh)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != Mesh)
        return;

    this->EquipAnimInProgress = false;
    UE_LOG(LogWeaponComponent, Warning, TEXT("Finished equip"));
}

void USTMWeaponComponent::OnReloadFinish(USkeletalMeshComponent *Mesh)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != Mesh)
        return;

    this->ReloadAnimInProgress = false;
    UE_LOG(LogWeaponComponent, Warning, TEXT("Finished reload"));
    this->CurrentWeapon->ChangeClip();
}

bool USTMWeaponComponent::CanFire() const
{
    return (CurrentWeapon && !this->EquipAnimInProgress && !ReloadAnimInProgress);
}

bool USTMWeaponComponent::CanEquip() const
{
    return (!this->EquipAnimInProgress && !ReloadAnimInProgress);
}

bool USTMWeaponComponent::CanReload() const
{
    return (CurrentWeapon && !this->EquipAnimInProgress && !ReloadAnimInProgress && this->CurrentWeapon->CanReload());
}

void USTMWeaponComponent::OnEmptyClip(ASTMBaseWeapon *AmmoEmptyWeapon)
{
    if (!AmmoEmptyWeapon)
        return;
    if (AmmoEmptyWeapon == this->CurrentWeapon)
        this->ChangeClip();
    else
        AmmoEmptyWeapon->ChangeClip();
}

void USTMWeaponComponent::ChangeClip()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || !this->CanReload())
        return;
    this->CurrentWeapon->StopFire();
    this->ReloadAnimInProgress = true;
    Character->PlayAnimMontage(this->CurrentReloadMontage);
}
