// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

class UNiagaraComponent;
class USTMWeaponVFXComponent;
class UNiagaraSystem;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;
    void MakeDamage(FHitResult &HitResult);
    void MakeHit(FHitResult &HitResult, FVector &TraceStart, FVector &TraceEnd);

  private:
    UPROPERTY()
    UNiagaraComponent *MuzzleFXComponent;
    FTimerHandle ShotTimerHandle;

    void InitMuzzleFX();
    void SetMuzzleVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
    AController *GetController() const;
};
