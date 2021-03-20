// ShootTheMap


#include "PickUps/STMHealthPickUp.h"
#include "Characters/Components/HealthComponent.h"
#include "STMUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);

bool ASTMHealthPickUp::GivePickUpTo(APawn *Player)
{
    const auto Health = STMUtils::GetComponent<UHealthComponent>(Player);
    if (!Health || Health->IsDead())
        return (false);

    UE_LOG(LogHealthPickUp, Display, TEXT("Health taken!"));
    return (Health->TryToAddHealth(this->HealthAmount));
}
