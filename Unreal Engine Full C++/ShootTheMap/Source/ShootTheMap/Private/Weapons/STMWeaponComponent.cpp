// ShootTheMap

#include "Weapons/STMWeaponComponent.h"
#include "Weapons/STMBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Characters/STMBaseCharacter.h"

// Sets default values for this component's properties
USTMWeaponComponent::USTMWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void USTMWeaponComponent::OnFire()
{
    if (!this->CurrentWeapon) return;

    this->CurrentWeapon->Fire();
}

// Called when the game starts
void USTMWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    this->SpawnWeapon();
    ASTMBaseCharacter *CurrentCharacterTemp = Cast<ASTMBaseCharacter>(GetOwner());
    if (CurrentCharacterTemp)
        CurrentCharacterTemp->OnDestroyWeapon.AddUObject(this, &USTMWeaponComponent::DestroyWeapon);
}

void USTMWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    this->CurrentWeapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(this->WeaponClass);
    if (!this->CurrentWeapon) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    this->CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, this->WeaponAttachPointName);
    this->CurrentWeapon->SetOwner(Character);

}

void USTMWeaponComponent::DestroyWeapon()
{
    GetWorld()->DestroyActor(this->CurrentWeapon);
}
