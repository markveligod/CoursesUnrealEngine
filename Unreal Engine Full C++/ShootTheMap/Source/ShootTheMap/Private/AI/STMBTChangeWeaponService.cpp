// ShootTheMap


#include "AI/STMBTChangeWeaponService.h"
#include "Weapons/STMWeaponComponent.h"
#include "AIController.h"
#include "STMUtils.h"


USTMBTChangeWeaponService::USTMBTChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTMBTChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = STMUtils::GetComponent<USTMWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && this->Probability > 0 && FMath::FRand() <= this->Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
