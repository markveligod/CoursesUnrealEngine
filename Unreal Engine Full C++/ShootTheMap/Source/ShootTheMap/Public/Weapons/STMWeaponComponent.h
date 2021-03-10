// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
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

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    TArray<TSubclassOf<ASTMBaseWeapon>> WeaponClasses;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditAnywhere, Category = "Weapons")
    FName WeaponArmorySocketName = "ArmorySocket";

  private:
    UPROPERTY()
    ASTMBaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASTMBaseWeapon *> WeaponsPtr;

    int32 CurrentIndexWeapon = 0;


    void AttachWeaponToSocket(ASTMBaseWeapon *Weapon, USceneComponent *Mesh, const FName &Socket);
    void SpawnWeapons();
    void EquipWeapon(int32 WeaponIndex);
};
