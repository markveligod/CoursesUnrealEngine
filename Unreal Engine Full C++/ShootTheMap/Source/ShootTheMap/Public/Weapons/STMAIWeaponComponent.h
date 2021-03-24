// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMWeaponComponent.h"
#include "STMAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API USTMAIWeaponComponent : public USTMWeaponComponent
{
    GENERATED_BODY()
  public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
