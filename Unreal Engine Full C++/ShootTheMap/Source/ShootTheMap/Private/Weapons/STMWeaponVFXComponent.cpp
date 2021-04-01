// ShootTheMap

#include "Weapons/STMWeaponVFXComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Sound/SoundCue.h"

// Sets default values
USTMWeaponVFXComponent::USTMWeaponVFXComponent()
{
}

void USTMWeaponVFXComponent::PlayImpact(const FHitResult &Hit)
{
    auto ImpactData = this->DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto Phys = Hit.PhysMaterial.Get();
        if (this->ImpactDataMap.Contains(Phys))
        {
            ImpactData = this->ImpactDataMap[Phys];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),               //
                                                   ImpactData.NiagaraEffect, //
                                                   Hit.ImpactPoint,          //
                                                   Hit.ImpactNormal.Rotation());

    auto DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),                    //
                                                            ImpactData.DecalData.Material, //
                                                            ImpactData.DecalData.Size,     //
                                                            Hit.ImpactPoint,               //
                                                            Hit.ImpactNormal.Rotation());
    if (DecalComp)
    {
        DecalComp->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }

    //sound
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, Hit.ImpactPoint);
}
