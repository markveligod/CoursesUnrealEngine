// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

class USTMWeaponVFXComponent;

/**
 *
 */
UCLASS()
class SHOOTTHEMAP_API ASTMRifleWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()
  public:
    ASTMRifleWeapon();
    virtual void StartFire() override;
    virtual void StopFire() override;
    
  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    float BulletSpreed = 1.5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    float DamageAmount = 10.f;

    UPROPERTY(VisibleAnyWhere, Category = "VFX")
    USTMWeaponVFXComponent *WeaponVFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;
    void MakeDamage(FHitResult &HitResult);
    void MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd);
  private:
    FTimerHandle ShotTimerHandle;
};
