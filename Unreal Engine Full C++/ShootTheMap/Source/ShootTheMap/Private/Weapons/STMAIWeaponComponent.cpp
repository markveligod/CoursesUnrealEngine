// ShootTheMap


#include "Weapons/STMAIWeaponComponent.h"
#include "Weapons/STMBaseWeapon.h"


void USTMAIWeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void USTMAIWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    int32 NextIndex = (CurrentIndexWeapon + 1) % WeaponsPtr.Num();
    while (NextIndex != CurrentIndexWeapon)
    {
        if (!WeaponsPtr[NextIndex]->IsAmmoEmpty())
            break;
        NextIndex = (NextIndex + 1) % WeaponsPtr.Num();
    }
    if (NextIndex != CurrentIndexWeapon)
    {
        CurrentIndexWeapon = NextIndex;
        EquipWeapon(CurrentIndexWeapon);
    }

}
