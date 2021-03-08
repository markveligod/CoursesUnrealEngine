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

    void OnFire();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;

    UPROPERTY(EditAnywhere, Category = "Weapons")
    FName WeaponAttachPointName = "WeaponSocket";
  private:
    UPROPERTY()
    ASTMBaseWeapon *CurrentWeapon = nullptr;

    void SpawnWeapon();
};
