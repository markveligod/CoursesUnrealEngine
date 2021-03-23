// ShootTheMap


#include "AI/STMAIController.h"
#include "AI/STMAICharacter.h"
#include "AI/STMAIPerceptionComponent.h"

ASTMAIController::ASTMAIController()
{
    this->STMAIPerceptionComponent = CreateDefaultSubobject<USTMAIPerceptionComponent>("STMAIPerceptionComponent");
    SetPerceptionComponent(*STMAIPerceptionComponent);
}

void ASTMAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ASTMAICharacter>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void ASTMAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    auto AimActor = this->STMAIPerceptionComponent->GetClosesEnemy();
    SetFocus(AimActor);
}
