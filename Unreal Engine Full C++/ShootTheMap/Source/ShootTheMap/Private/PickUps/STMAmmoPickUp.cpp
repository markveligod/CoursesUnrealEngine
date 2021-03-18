// ShootTheMap


#include "PickUps/STMAmmoPickUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);

bool ASTMAmmoPickUp::GivePickUpTo(APawn *Player)
{
    UE_LOG(LogAmmoPickUp, Display, TEXT("Ammo Lost taken!"));
    return true;
}
