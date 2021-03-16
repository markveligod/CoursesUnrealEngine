// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STMWeaponComponent.generated.h"

class ASTMBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    UAnimMontage *AnimReload;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMAP_API USTMWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    USTMWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

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

    int32 CurrentIndexWeapon = 0;

    bool AnimInProgress = false;

    void AttachWeaponToSocket(ASTMBaseWeapon *Weapon, USceneComponent *Mesh, const FName &Socket);
    void SpawnWeapons();
    void EquipWeapon(int32 WeaponIndex);
    void AnimEquip(UAnimMontage *Animation);
    void InitAnimations();
    void OnEquipFinish(USkeletalMeshComponent *Mesh);
    bool CanFire() const;
    bool CanEquip() const;
};
