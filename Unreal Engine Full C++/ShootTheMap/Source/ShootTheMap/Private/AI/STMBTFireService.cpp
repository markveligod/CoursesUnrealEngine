// ShootTheMap


#include "AI/STMBTFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Weapons/STMWeaponComponent.h"
#include "STMUtils.h"


USTMBTFireService::USTMBTFireService()
{
    NodeName = "Fire";
}

void USTMBTFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(this->EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = STMUtils::GetComponent<USTMWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
