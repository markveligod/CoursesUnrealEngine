// ShootTheMap


#include "PickUps/STMHealthPickUp.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);

bool ASTMHealthPickUp::GivePickUpTo(APawn *Player)
{
    UE_LOG(LogHealthPickUp, Display, TEXT("Health Lost taken!"));
    return true;
}
