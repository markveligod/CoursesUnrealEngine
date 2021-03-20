// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTMWeaponVFXComponent;

UCLASS()
class SHOOTTHEMAP_API ASTMProjectile : public AActor
{
    GENERATED_BODY()

  public:
    ASTMProjectile();
    void SetShotDirection(const FVector Direction);
  protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;


    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float DamageRadius = 200.f;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float DamageAmount = 50.f;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float LifeSeconds = 5.f;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    bool DoFullDamage = false;

    UPROPERTY(VisibleAnyWhere, Category = "VFX")
    USTMWeaponVFXComponent *WeaponVFXComponent;

    virtual void BeginPlay() override;

  private:
    FVector ShootDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    AController *GetController() const;
};
