// ShootTheMap


#include "PickUps/STMAmmoPickUp.h"
#include "Weapons/STMWeaponComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "STMUtils.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);

bool ASTMAmmoPickUp::GivePickUpTo(APawn *Player)
{
    const auto Health = STMUtils::GetComponent<UHealthComponent>(Player);
    if (!Health || Health->IsDead())
        return (false);

    const auto Weapon = STMUtils::GetComponent<USTMWeaponComponent>(Player);
    if (!Weapon)
        return (false);

    UE_LOG(LogAmmoPickUp, Display, TEXT("Ammo taken!"));
    return (Weapon->TryToAddAmmo(this->WeaponType, this->ClipsAmount));
}
