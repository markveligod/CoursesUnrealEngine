// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "STMWeaponComponent.generated.h"

class ASTMBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMAP_API USTMWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    USTMWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();

    bool GetWeaponUIData(FWeaponUIData &UIData);
    bool GetAmmoUIData(FAmmoData &AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType, int32 ClipsAmount);

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    TArray<FWeaponData> WeaponDates;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditAnywhere, Category = "Weapons")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditAnywhere, Category = "Weapons")
    UAnimMontage *AnimationEquip;

  private:
    UPROPERTY()
    ASTMBaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTMBaseWeapon *> WeaponsPtr;

    UPROPERTY()
    UAnimMontage *CurrentReloadMontage = nullptr;

    int32 CurrentIndexWeapon = 0;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void AttachWeaponToSocket(ASTMBaseWeapon *Weapon, USceneComponent *Mesh, const FName &Socket);
    void SpawnWeapons();
    void EquipWeapon(int32 WeaponIndex);
    void AnimEquip(UAnimMontage *Animation);
    void InitAnimations();

    void OnEquipFinish(USkeletalMeshComponent *Mesh);
    void OnReloadFinish(USkeletalMeshComponent *Mesh);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    void OnEmptyClip(ASTMBaseWeapon *AmmoEmptyWeapon);
    void ChangeClip();

};

