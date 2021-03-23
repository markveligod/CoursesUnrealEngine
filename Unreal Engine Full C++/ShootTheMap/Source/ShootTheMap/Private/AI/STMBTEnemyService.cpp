// ShootTheMap


#include "AI/STMBTEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STMAIController.h"
#include "STMUtils.h"
#include "STMAIPerceptionComponent.h"

USTMBTEnemyService::USTMBTEnemyService()
{
    NodeName = "Find Enemy";
}

void USTMBTEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = STMUtils::GetComponent<USTMAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(this->EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
        }
        Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    }
}
