// ShootTheMap

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STMCoreType.h"
#include "STMWeaponVFXComponent.generated.h"


class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS()
class SHOOTTHEMAP_API USTMWeaponVFXComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    USTMWeaponVFXComponent();

    void PlayImpact(const FHitResult &Hit);

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial *, FImpactData> ImpactDataMap;
};
