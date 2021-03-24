// ShootTheMap


#include "AI/STMHealthPercentBTDecorator.h"
#include "AIController.h"
#include "STMUtils.h"
#include "Characters/Components/HealthComponent.h"

USTMHealthPercentBTDecorator::USTMHealthPercentBTDecorator()
{
    NodeName = "Health Precent";
}

bool USTMHealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;
    const auto HealthComp = STMUtils::GetComponent<UHealthComponent>(Controller->GetPawn());
    if (!HealthComp || HealthComp->IsDead())
        return false;

    return (HealthComp->GetHealthPercent() <= this->HealthPrecent);
}

