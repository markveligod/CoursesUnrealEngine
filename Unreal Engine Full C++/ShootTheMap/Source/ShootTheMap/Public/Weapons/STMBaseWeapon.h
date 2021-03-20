// ShootTheMap

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMCoreType.h"
#include "STMBaseWeapon.generated.h"


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

    virtual void BeginPlay() override;

    APlayerController *GetPlayerController() const;
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void LogAmmo();

    bool IsAmmoFull() const;

  private:
    FAmmoData CurrentAmmo;
};
