// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMCoreType.h"
#include "STMBaseWeapon.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMAP_API ASTMBaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    ASTMBaseWeapon();

    FOnClimpEmptySignature OnClimpEmptySignature;

    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const;

    FAmmoData GetAmmoData() const;

    bool TryToAddAmmo(int32 ClipsAmount);

    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    float TraceMaxDistance = 1500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit Weapon")
    FAmmoData DefaultAmmoData{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edit VFX")
    UNiagaraSystem *MuzzleFX;

    virtual void BeginPlay() override;

    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

    void DecreaseAmmo();
    bool IsClipEmpty() const;
    void LogAmmo();

    UNiagaraComponent *SpawnMuzzleFX();
  private:
    FAmmoData CurrentAmmo;
};
