// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMBaseWeapon.h"
#include "STMLauncherWeapon.generated.h"

/**
 *
 */

class ASTMProjectile;
class USoundCue;

UCLASS()
class SHOOTTHEMAP_API ASTMLauncherWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()
  public:
    virtual void StartFire() override;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound Editor")
    USoundCue *NoAmmoSound;

    virtual void MakeShot() override;
};
