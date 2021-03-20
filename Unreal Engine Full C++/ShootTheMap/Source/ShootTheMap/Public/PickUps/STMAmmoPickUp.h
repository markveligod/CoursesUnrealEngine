// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "PickUps/STMBasePickUp.h"
#include "STMAmmoPickUp.generated.h"

class ASTMBaseWeapon;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMAmmoPickUp : public ASTMBasePickUp
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "10"))
    int32 ClipsAmount = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASTMBaseWeapon> WeaponType;

  private:
    virtual bool GivePickUpTo(APawn *Player) override;
};
