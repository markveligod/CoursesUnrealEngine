// ShootTheMap

#include "AI/STMBTFindAmmoDecorator.h"
#include "AIController.h"
#include "STMUtils.h"
#include "Weapons/STMWeaponComponent.h"

USTMBTFindAmmoDecorator::USTMBTFindAmmoDecorator()
{
    NodeName = "Decorator Ammo";
}

bool USTMBTFindAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;
    const auto WeaponComp = STMUtils::GetComponent<USTMWeaponComponent>(Controller->GetPawn());
    if (!WeaponComp)
        return false;
    return (WeaponComp->NeedAmmo(this->TypeWeapon));
}
