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
  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    float HealthAmount = 50.f;

  private:
    virtual bool GivePickUpTo(APawn *Player) override;
};
