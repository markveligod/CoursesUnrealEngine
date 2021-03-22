// ShootTheMap


#include "AI/Tasks/BTNextLocationTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STMAIController.h"
#include "NavigationSystem.h"

UBTNextLocationTaskNode::UBTNextLocationTaskNode()
{
    NodeName = "NextLocation";
}

EBTNodeResult::Type UBTNextLocationTaskNode::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackbourd = OwnerComp.GetBlackboardComponent();

    if (!Controller || !Blackbourd)
        return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return EBTNodeResult::Failed;

    const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSystem)
        return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    const auto Found = NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), this->Radius, NavLocation);
    if (!Found)
        return EBTNodeResult::Failed;

    Blackbourd->SetValueAsVector(this->AimLocationKey.SelectedKeyName, NavLocation.Location);
    return EBTNodeResult::Succeeded;
}
