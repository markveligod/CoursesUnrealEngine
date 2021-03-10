// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMRifleWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()
  public:
    virtual void StartFire() override;
    virtual void StopFire() override;

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float BulletSpreed = 1.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;
    void MakeDamage(FHitResult &HitResult);
    void MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd);
  private:
    FTimerHandle ShotTimerHandle;
};
