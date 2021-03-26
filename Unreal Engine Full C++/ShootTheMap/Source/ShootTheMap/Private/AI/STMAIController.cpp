// ShootTheMap


#include "AI/STMAIController.h"
#include "AI/STMAICharacter.h"
#include "AI/STMAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerControllers/STMRestartComponent.h"

ASTMAIController::ASTMAIController()
{
    this->STMAIPerceptionComponent = CreateDefaultSubobject<USTMAIPerceptionComponent>("STMAIPerceptionComponent");
    SetPerceptionComponent(*STMAIPerceptionComponent);

    this->STMRestartComponent = CreateDefaultSubobject<USTMRestartComponent>("Restart Component");


    bWantsPlayerState = true;
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
    auto AimActor = this->GetFocusActor();
    SetFocus(AimActor);
}

AActor * ASTMAIController::GetFocusActor() const
{
    if (!GetBlackboardComponent())
        return nullptr;
    return (Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(this->FocusOnKeyName)));
}
