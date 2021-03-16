// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
    int32 Bullet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (EditCondition = "!bInfinity"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
    bool bInfinity;
};


UCLASS()
class SHOOTTHEMAP_API ASTMBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ASTMBaseWeapon();

    virtual void StartFire();
    virtual void StopFire();

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    FAmmoData DefaultAmmoData{15,10,false};


    virtual void BeginPlay() override;

    APlayerController *GetPlayerController() const;
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void ChangeClip();
    void LogAmmo();
  private:
    FAmmoData CurrentAmmo;

};


