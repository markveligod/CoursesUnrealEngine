// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STMBasePickUp.h"
#include "STMHealthPickUp.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMHealthPickUp : public ASTMBasePickUp
{
    GENERATED_BODY()
  private:
    virtual bool GivePickUpTo(APawn *Player) override;
};
