// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMBaseWeapon.h"
#include "STMLauncherWeapon.generated.h"

/**
 *
 */

class ASTMProjectile;

UCLASS()
class SHOOTTHEMAP_API ASTMLauncherWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()
  public:
    virtual void StartFire() override;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMProjectile> ProjectileClass;


    virtual void MakeShot() override;
};
