// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STMBasePickUp.h"
#include "STMAmmoPickUp.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMAmmoPickUp : public ASTMBasePickUp
{
    GENERATED_BODY()
  private:
    virtual bool GivePickUpTo(APawn *Player) override;
};
